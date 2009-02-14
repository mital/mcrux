#pragma once

#include <comdef.h>
#include <winsock2.h>

#include <zlib.h>
#include <openssl/ssl.h>


class CSocket  
{
private:
	CRITICAL_SECTION m_csReading;
	CRITICAL_SECTION m_csWriting;

	SOCKET  m_Socket;

	z_stream    compressionStream;
	z_stream    decompressionStream;

	BYTE*       pendingCompressed;
	bool		decHasMoreInput;

	BOOL		m_bConnected;
	BOOL		m_bUsingSSL;
	BOOL		m_bUsingSC;
	SSL			*m_ssl;
	SSL_CTX		*m_ctxClient;						// Pointer to SSL context for outbound sockets.

	DWORD   AssureWSAInit();
	DWORD   LookupAddress( _bstr_t ServerAddress );
public:
	CSocket( SOCKET s = INVALID_SOCKET );
	~CSocket();

	DWORD   Init();
	DWORD   Connect( _bstr_t ServerAddress, WORD wPort );
	DWORD   Disconnect();

	DWORD	StartTLS();
	DWORD   StartSC();
	
	int     Select( bool bRead, bool bWrite, timeval *tv = NULL);
	BOOL    SetTimeout( DWORD nSeconds );

	USHORT  Listen( WORD nPort );
	CSocket* Accept();

	DWORD   Send( BYTE* buf, DWORD nBufLen );
	DWORD	Recv( BYTE* buf, DWORD nBufLen );

	DWORD	SendLine( LPWSTR str );
/*	DWORD	RecvLine( LPTSTR *str ); */

	_bstr_t GetRemoteAddress();
	WORD    GetRemotePort();
	_bstr_t GetLocalAddress();
	WORD	GetLocalPort();
	SOCKET	GetHandle();
};
