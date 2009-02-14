#include "stdafx.h"
#include "Socket.h"
#include "utf.h"

#include <tchar.h>
#include <strsafe.h>


void compressionMessage( int uncompressed, int compressed, bool recv )
{
	static int overallComp = 0, overallUncomp = 0;
	overallComp += compressed;
	overallUncomp += uncompressed;

	TCHAR debugmsg[512];
	StringCbPrintf( debugmsg, 512, _T("%s\tsize: %d bytes\tcompressed size: %d bytes\tratio: %f\toverall ratio: %f\n"),
		recv ? _T("RECEIVING") : _T("SENDING"), uncompressed, compressed, (float)compressed/(float)uncompressed,
		(float)overallComp/(float)overallUncomp );
#ifdef _DEBUG
	OutputDebugString( debugmsg );
#endif
}

CSocket::CSocket( SOCKET s ): m_Socket(s), m_bUsingSSL(0), m_bUsingSC(0), m_ssl(NULL), m_ctxClient(NULL), m_bConnected(false), pendingCompressed(NULL), decHasMoreInput(false)
{
	InitializeCriticalSection( &m_csReading );
	InitializeCriticalSection( &m_csWriting );

	if( m_Socket == INVALID_SOCKET )
	{
        m_Socket = socket( AF_INET, SOCK_STREAM, 0 );
	}
}
CSocket::~CSocket()
{
	Disconnect();

	if( m_ssl )
	{
		SSL_free( m_ssl );
	}
	if( m_ctxClient )
	{
		SSL_CTX_free( m_ctxClient );
	}
	if( m_bUsingSC )
	{
		deflateEnd( &compressionStream );
		inflateEnd( &decompressionStream );
		if( pendingCompressed )
			delete pendingCompressed;
	}
	DeleteCriticalSection( &m_csReading );
	DeleteCriticalSection( &m_csWriting );
}
BOOL CSocket::SetTimeout( DWORD nSeconds )
{
	DWORD dwMSecs = nSeconds * 1000;

	setsockopt( m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*) &dwMSecs, sizeof(DWORD) );
	setsockopt( m_Socket, SOL_SOCKET, SO_SNDTIMEO, (char*) &dwMSecs, sizeof(DWORD) );

	return true;
}

DWORD CSocket::Connect( _bstr_t ServerAddress, WORD wPort )
{
	EnterCriticalSection( &m_csReading );
	EnterCriticalSection( &m_csWriting );
	sockaddr_in sinRemote;
	sinRemote.sin_family = AF_INET;
	sinRemote.sin_addr.s_addr = LookupAddress( ServerAddress );
	sinRemote.sin_port = htons(wPort);
	
	if( connect( m_Socket, (sockaddr*)&sinRemote, sizeof(sockaddr_in) ) == SOCKET_ERROR )
	{
		LeaveCriticalSection( &m_csReading );
		LeaveCriticalSection( &m_csWriting );
		return WSAGetLastError();
	}

	m_bConnected = true;
	LeaveCriticalSection( &m_csReading );
	LeaveCriticalSection( &m_csWriting );
	return 0;
}

DWORD CSocket::Disconnect()
{
	EnterCriticalSection( &m_csReading );
	EnterCriticalSection( &m_csWriting );
	if( m_Socket == INVALID_SOCKET )
		return 0;

	if(m_ssl)
	{
		SSL_shutdown(m_ssl);
	}

	shutdown( m_Socket, SD_BOTH );

	SOCKET stackSocket = m_Socket;
	m_Socket = INVALID_SOCKET;
	m_bConnected = false;
	LeaveCriticalSection( &m_csReading );
	LeaveCriticalSection( &m_csWriting );
	return closesocket( stackSocket );
}

DWORD CSocket::StartTLS()
{
	EnterCriticalSection( &m_csReading );
	EnterCriticalSection( &m_csWriting );

	DWORD arg = 0;
	ioctlsocket( m_Socket, FIONBIO, &arg );

	if( m_bConnected )
	{
		m_ctxClient = SSL_CTX_new( SSLv23_client_method() );
		if( m_ctxClient )
		{
			m_ssl = SSL_new( m_ctxClient );
			if( m_ssl )
			{
				BIO *bioSSL;
				bioSSL = BIO_new_socket( m_Socket, BIO_NOCLOSE );
				BIO_set_buffer_size( bioSSL, 0xFFFF );
				BIO_set_nbio( bioSSL, true );

				if( bioSSL )
				{
					SSL_set_bio( m_ssl, bioSSL, bioSSL );	// Set SSL I/O routines for this call.
					// Start the actual TLS/SSL handshake.
					if( SSL_connect( m_ssl ) == 1 )
					{
						if( SSL_do_handshake( m_ssl ) )
						{
                            m_bUsingSSL = true;
							LeaveCriticalSection( &m_csReading );
							LeaveCriticalSection( &m_csWriting );
                            return 1;
						}
					}
				}
			}
		}
	}

	arg = 1;
	ioctlsocket( m_Socket, FIONBIO, &arg );

	LeaveCriticalSection( &m_csReading );
	LeaveCriticalSection( &m_csWriting );
	return 0;
}

DWORD CSocket::StartSC()
{
	EnterCriticalSection( &m_csReading );
	EnterCriticalSection( &m_csWriting );

	compressionStream.zalloc = Z_NULL;
	compressionStream.zfree = Z_NULL;
	compressionStream.opaque = Z_NULL;

	decompressionStream.next_in = Z_NULL;
	decompressionStream.avail_in = 0;
	decompressionStream.zalloc = Z_NULL;
	decompressionStream.zfree = Z_NULL;
	decompressionStream.opaque = Z_NULL;

	if( deflateInit( &compressionStream, 9 ) == Z_OK &&
		inflateInit( &decompressionStream ) == Z_OK )
	{
		m_bUsingSC = true;
		LeaveCriticalSection( &m_csReading );
		LeaveCriticalSection( &m_csWriting );
		return 1;
	}

	LeaveCriticalSection( &m_csReading );
	LeaveCriticalSection( &m_csWriting );
	return 0;
}

DWORD CSocket::LookupAddress( _bstr_t ServerAddress )
{
	u_long nRemoteAddress = inet_addr( ServerAddress );
	if( nRemoteAddress == INADDR_NONE ) {
		hostent* pHE = gethostbyname( ServerAddress );
        if( pHE == 0 )
           return INADDR_NONE;
		nRemoteAddress = *((u_long*)pHE->h_addr_list[0]);
	}
	return nRemoteAddress;
}

USHORT CSocket::Listen(WORD nPort)
{
	sockaddr_in sinLocal;
	sinLocal.sin_family = AF_INET;
	sinLocal.sin_addr.s_addr = LookupAddress( "0.0.0.0" );
	sinLocal.sin_port = htons(nPort);

	if( bind( m_Socket, (sockaddr*) &sinLocal, sizeof(sockaddr_in) ) )
		return 0;
	if( listen( m_Socket, SOMAXCONN ) )
		return 0;

	int namelen = sizeof(sockaddr);
	getsockname( m_Socket, (sockaddr*) &sinLocal, &namelen );

	return ntohs(sinLocal.sin_port);
}

CSocket* CSocket::Accept()
{
	SOCKET s = accept( m_Socket, 0, 0 );

	if( s == INVALID_SOCKET )
		return NULL;

	return new CSocket( s );
}

DWORD CSocket::Send( BYTE *buf, DWORD nBufLen )
{
	EnterCriticalSection( &m_csWriting );
	int iResult;

	BYTE *outputBuffer = buf;
	DWORD outputSize = nBufLen;
	if( m_bUsingSC )
	{
		compressionStream.next_in = buf;
		compressionStream.avail_in = nBufLen;

		outputSize = nBufLen + nBufLen / 1000 + 12;
		outputBuffer = new BYTE[outputSize];
		compressionStream.next_out = outputBuffer;
		compressionStream.avail_out = outputSize;

		deflate( &compressionStream, Z_SYNC_FLUSH );

		outputSize -= compressionStream.avail_out;

		compressionMessage( nBufLen, outputSize, false );
	}
	if( m_bUsingSSL )
	{
		while( true )
		{
            iResult = SSL_write( m_ssl, outputBuffer, outputSize );
			if( SSL_get_error( m_ssl, iResult ) == SSL_ERROR_WANT_WRITE || 
				SSL_get_error( m_ssl, iResult ) == SSL_ERROR_WANT_READ )
			{
				Sleep( 1 );
				continue;
			}
			else
				break;
		}
	}
	else
	{
		iResult = send( m_Socket, (char*) outputBuffer, outputSize, 0 );
	}
	if( m_bUsingSC )
	{
		delete outputBuffer;
	}

    LeaveCriticalSection( &m_csWriting );
	return iResult;
}

DWORD CSocket::Recv( BYTE *buf, DWORD nBufLen )
{
	EnterCriticalSection( &m_csReading );
	int iResult;

	if( pendingCompressed )
	{
		int oldavail_in = decompressionStream.avail_in;
		decompressionStream.avail_out = nBufLen;
		decompressionStream.next_out = buf;

		inflate( &decompressionStream, Z_SYNC_FLUSH );

		if( decompressionStream.avail_in == 0 )
		{
			decHasMoreInput = false;
			delete pendingCompressed;
			pendingCompressed = NULL;
		}

		if( oldavail_in != decompressionStream.avail_in )
		{
			compressionMessage( nBufLen - decompressionStream.avail_out, oldavail_in - decompressionStream.avail_in, true );
            return nBufLen - decompressionStream.avail_out;
		}
		else
		{
			decHasMoreInput = false;
			/* nothing was decompressed, queue up some more bytes */
		}
	}
	if( m_bUsingSSL )
	{
		while( true )
		{
            iResult = SSL_read( m_ssl, buf, nBufLen );
			if( SSL_get_error( m_ssl, iResult ) == SSL_ERROR_WANT_WRITE || 
				SSL_get_error( m_ssl, iResult ) == SSL_ERROR_WANT_READ )
			{
				Sleep( 1 );
				//OutputDebugString( TEXT("SSL (read attempt) rehandshaking\n") );
				continue;
			}
			else
				break;
		}
	}
	else
	{
		iResult = recv( m_Socket, (char*) buf, nBufLen, 0 );
	}
	if( m_bUsingSC && iResult > 0 )
	{
		if( pendingCompressed )
		{
			BYTE *oldPendingCompressed = pendingCompressed;
			pendingCompressed = new BYTE[decompressionStream.avail_in+iResult];
			memcpy( pendingCompressed, oldPendingCompressed, decompressionStream.avail_in );
			memcpy( pendingCompressed + decompressionStream.avail_in, buf, iResult );
			decompressionStream.avail_in = decompressionStream.avail_in+iResult;
			delete oldPendingCompressed;
		}
		else
		{
			pendingCompressed = new BYTE[iResult];
			memcpy( pendingCompressed, buf, iResult );
			decompressionStream.avail_in = iResult;
		}

		int oldavail_in = decompressionStream.avail_in;
		decompressionStream.next_in = pendingCompressed;

		decompressionStream.avail_out = nBufLen;
		decompressionStream.next_out = buf;

		inflate( &decompressionStream, Z_SYNC_FLUSH );
		iResult = nBufLen - decompressionStream.avail_out;

		if( decompressionStream.avail_in == 0 )
		{
			decHasMoreInput = false;
			delete pendingCompressed;
			pendingCompressed = NULL;
		}
		else
			decHasMoreInput = true;

		compressionMessage( nBufLen - decompressionStream.avail_out, oldavail_in - decompressionStream.avail_in, true );
	}

	LeaveCriticalSection( &m_csReading );
	return iResult;
}

DWORD CSocket::SendLine( LPWSTR strLine )
{
	DWORD reqBufSize = UnicodeToUTF8( strLine, wcslen(strLine), 0, 0 );
	char *strUTF8 = new char[reqBufSize+2];
	UnicodeToUTF8( strLine, wcslen(strLine), strUTF8, reqBufSize );
	strUTF8[reqBufSize] = '\r';
	strUTF8[reqBufSize+1] = '\n';

	DWORD retVal = Send( (BYTE *)strUTF8, reqBufSize+2 );

	delete strUTF8;
	return retVal;
}
/*
DWORD CSocket::RecvLine( LPTSTR *str )
{

}
*/
_bstr_t CSocket::GetRemoteAddress()
{
	sockaddr_in sinRemote;
	int sinRemoteSize = sizeof(sockaddr_in);
	if( getpeername( m_Socket, (sockaddr*)&sinRemote, &sinRemoteSize ) )
		return "";
	TCHAR tmp[17];
	StringCbPrintf( tmp, 17, TEXT("%d.%d.%d.%d"),
		sinRemote.sin_addr.S_un.S_un_b.s_b1,
		sinRemote.sin_addr.S_un.S_un_b.s_b2,
		sinRemote.sin_addr.S_un.S_un_b.s_b3,
		sinRemote.sin_addr.S_un.S_un_b.s_b4 );
	_bstr_t foo = tmp;
	return foo;
}

WORD CSocket::GetRemotePort()
{
	sockaddr_in sinRemote;
	int sinRemoteSize = sizeof(sockaddr_in);
	if( getpeername( m_Socket, (sockaddr*)&sinRemote, &sinRemoteSize ) ){
		return 0;
	}

	return ntohs( sinRemote.sin_port );
}

_bstr_t CSocket::GetLocalAddress()
{
	sockaddr_in sinLocal;
	int sinLocalSize = sizeof(sockaddr_in);
	if( getsockname( m_Socket, (sockaddr*)&sinLocal, &sinLocalSize ) )
		return "";
	TCHAR tmp[17];
	StringCbPrintf( tmp, 17, TEXT("%d.%d.%d.%d"),
		sinLocal.sin_addr.S_un.S_un_b.s_b1,
		sinLocal.sin_addr.S_un.S_un_b.s_b2,
		sinLocal.sin_addr.S_un.S_un_b.s_b3,
		sinLocal.sin_addr.S_un.S_un_b.s_b4 );
	_bstr_t foo = tmp;
	return foo;
}

WORD CSocket::GetLocalPort()
{
	sockaddr_in sinLocal;
	int sinLocalSize = sizeof(sockaddr_in);
	if( getsockname( m_Socket, (sockaddr*)&sinLocal, &sinLocalSize ) )
		return 0;

	return ntohs( sinLocal.sin_port );
}

SOCKET CSocket::GetHandle()
{
	return m_Socket;
}

int CSocket::Select( bool bRead, bool bWrite, timeval *tv )
{
	if( bRead && decHasMoreInput ) // If we still have some compressed data to be read.
		return 1;
	if( bRead && m_ssl )	// If we're reading from an SSL socket, see if it's still got buffered data.
	{
			if( SSL_pending( m_ssl ) )
				return 1;	// Return 1 socket with data ready.
	}

	fd_set fdSet;
	FD_ZERO(&fdSet);
	FD_SET(m_Socket, &fdSet);

	return select(FD_SETSIZE, bRead ? &fdSet : NULL, bWrite ? &fdSet : NULL, NULL, tv);
}
