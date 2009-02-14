#include "stdafx.h"

#include "XMPP.h"
#include "Socket.h"
#include "MainWnd.h"
#include "utf.h"
#include "srv.h"

/* todo: give the buffer it's own class, clean up recordelementbegin */

class CAttributes
{
	const xmlChar **myAtts;
public:
	CAttributes( const xmlChar **atts )
	{
		myAtts = atts;
	}

	HRESULT getLength( int *pLength )
	{
		if( myAtts != NULL )
		{
			int i;
			for( i = 0; myAtts[i] != NULL; i+=2 );
			*pLength = i/2;
		}
		else
		{
			*pLength = 0;
		}
		return S_OK;
	}
    HRESULT getQName( int nIndex, wchar_t ** ppwchQName, int * ppchQName )
	{
		int len;
		getLength( &len );

		if( 0 <= nIndex && nIndex < len )
		{
			*ppwchQName = SysAllocString( CUTF82W( myAtts[ nIndex*2 ] ) );
			*ppchQName = wcslen( *ppwchQName );
		}
		else
		{
			*ppwchQName = SysAllocString( L"" );
			*ppchQName = 0;
		}

		return S_OK;
	}
	HRESULT getValue( int nIndex, wchar_t ** ppwchValue, int * pcchValue )
	{
		int len;
		getLength( &len );

		if( 0 <= nIndex && nIndex < len )
		{
			*ppwchValue = SysAllocString( CUTF82W( myAtts[ nIndex*2 + 1] ) );
			*pcchValue = wcslen( *ppwchValue );
		}
		else
		{
			*ppwchValue = SysAllocString( L"" );
			*pcchValue = 0;
		}

		return S_OK;
	}
};

CSendBuffer::CSendBuffer( CSocket *pSocket, BYTE *pBuffer, DWORD bufLen )
{
	m_pSocket = pSocket;
	m_Len = bufLen;
	if( m_Len > 0 )
	{
        m_pBuffer = new BYTE[m_Len];
		memcpy( m_pBuffer, pBuffer, m_Len );
	}
	else
		m_pBuffer = 0;
}
CSendBuffer::~CSendBuffer()
{
	if( m_Len > 0 )
		delete m_pBuffer;
}
DWORD CSendBuffer::Send()
{
	return m_pSocket->Send( m_pBuffer, m_Len );
}

CSendQueue::CSendQueue()
{
	m_bConnected = false;

	m_hDataAvailable = CreateEvent( NULL, TRUE, FALSE, NULL );
	InitializeCriticalSection( &m_csAccessingQueue );

	DWORD ThreadID;
	m_hThread = CreateThread( NULL, NULL, SendQueueProc, this, 0, &ThreadID );
}
CSendQueue::~CSendQueue()
{
	TerminateThread( m_hThread, 0 );
	CloseHandle( m_hThread );

	DeleteCriticalSection( &m_csAccessingQueue );
	CloseHandle( m_hDataAvailable );
}
void CSendQueue::AddData( CSocket *pSocket, BYTE *data, DWORD len )
{
	EnterCriticalSection( &m_csAccessingQueue );
	if( m_bConnected )
	{
		m_Buffers.AddTail( new CSendBuffer( pSocket, data, len ) );
		SetEvent( m_hDataAvailable );
	}
	LeaveCriticalSection( &m_csAccessingQueue );
}
DWORD CSendQueue::SendData()
{
	DWORD dwRet = 0;
	EnterCriticalSection( &m_csAccessingQueue );
	if( m_bConnected )
	{
		CSendBuffer *sendBuf = m_Buffers.GetHead();
		LeaveCriticalSection( &m_csAccessingQueue );

		dwRet = sendBuf->Send();
		delete sendBuf;

		EnterCriticalSection( &m_csAccessingQueue );
		m_Buffers.RemoveHead();
	}
	LeaveCriticalSection( &m_csAccessingQueue );
	return dwRet;
}
void CSendQueue::SetConnected()
{
	EnterCriticalSection( &m_csAccessingQueue );
	m_Buffers.RemoveAll();
	m_bConnected = true;
	LeaveCriticalSection( &m_csAccessingQueue );
}
void CSendQueue::SetDisconnected()
{
	EnterCriticalSection( &m_csAccessingQueue );
	m_bConnected = false;
	LeaveCriticalSection( &m_csAccessingQueue );
}
DWORD __stdcall CSendQueue::SendQueueProc( void *pThis )
{
	((CSendQueue *)pThis)->WaitForData();
	return 0;
}
void CSendQueue::WaitForData()
{
	while( WaitForSingleObject( m_hDataAvailable, INFINITE ) == WAIT_OBJECT_0 )
	{
		SendData();

		EnterCriticalSection( &m_csAccessingQueue );
		if( m_Buffers.IsEmpty() )
		{
			ResetEvent( m_hDataAvailable );
		}
		LeaveCriticalSection( &m_csAccessingQueue );
	}
}

CXMPP::CXMPP() :
	m_ConnectedHandler( "" ), m_IQHandler( "" ), m_MessageHandler( "" ), m_PresenceHandler( "" ),
	m_DocumentStartHandler( "" ), m_DocumentEndHandler( "" ), m_StreamHandler( "" ),
	m_StartTLSSucceededHandler( "" ), m_StartTLSFailedHandler( "" ),
	m_StartSCSucceededHandler( "" ), m_StartSCFailedHandler( "" ),
	m_pSocket( NULL ), m_pMainWnd( NULL ), m_Server( "" ), m_Port( 0 ), m_nLevel( 0 ), m_bRestartParser( false ),
	m_bFirstRead( true ), m_ProxyMethod( 0 ), m_ProxyServer( "" ), m_ProxyPort( 0 ), m_ProxyPollURL( "" ),
	m_ProxyUsername( "" ), m_ProxyPassword( "" )
{
	xmlbufferleft = 16 * 1024;
	xmlbuffer = new wchar_t[xmlbufferleft];
	xmlbufferp = xmlbuffer;
	m_namespaces.InitHashTable( 100 );
	InitializeCriticalSection( &m_csDisconnecting );
	InitializeCriticalSection( &m_csStartTLS );
}
CXMPP::~CXMPP()
{
	delete xmlbuffer;
	if( m_pMainWnd )
		m_pMainWnd->Release();
	DeleteCriticalSection( &m_csDisconnecting );
	DeleteCriticalSection( &m_csStartTLS );
}

void CXMPP::SetServer( BSTR server )
{
	m_Server = server;
}
void CXMPP::SetPort( USHORT port )
{
	m_Port = port;
}
void CXMPP::UseSSL( BOOL b )
{
	m_UseSSL = b;
}

STDMETHODIMP CXMPP::SetMainWnd( void *pMainWnd )
{
	m_pMainWnd = (CMainWnd *) pMainWnd;
	m_pMainWnd->AddRef();
	return S_OK;
}
STDMETHODIMP CXMPP::Connect( BSTR server, USHORT port, BOOL useSSL, DWORD proxyMethod )
{
	SetServer( server );
	SetPort( port );
	UseSSL( useSSL );

	m_ProxyMethod = proxyMethod;

	DWORD ThreadID;
	CreateThread( NULL, 0, AsyncConnectProc, (void *)this, 0, &ThreadID );

	/* always return S_OK or S_FALSE, otherwise JScript goes crazy */
	return S_OK;
}
DWORD __stdcall CXMPP::AsyncConnectProc( void *pThis )
{
	return ((CXMPP *) pThis)->AsyncConnect();
}
DWORD CXMPP::AsyncConnect()
{
	CoInitialize( NULL );
//	OutputDebugString( TEXT("CXMPP::AsyncConnect(): Connecting to XMPP server...\n") );

	m_pSocket = new CSocket();

	BSTR srvname;
	WORD srvport;
	if( !SRVLookup( CComBSTR("xmpp-client"), CComBSTR("tcp"), m_Server, &srvport, &srvname ) )
	{
//		OutputDebugString( TEXT("CXMPP::AsyncConnect(): SRV lookup succeeded...\n") );
        m_Server = srvname;
		
		if( m_ProxyMethod == PROXY_METHOD_DONTUSE )
		{
			if( srvport != 0 && !m_UseSSL )
			{
				m_Port = srvport;
			}
		}
	}

	DWORD err = -1;
	if( m_ProxyMethod == PROXY_METHOD_DONTUSE )
	{
		err = m_pSocket->Connect( (BSTR) m_Server, m_Port );
	}
	else if( m_ProxyMethod == PROXY_METHOD_CONNECT )
	{
		err = m_pSocket->Connect( (BSTR) m_ProxyServer, m_ProxyPort );
		if( !err )
		{
			WCHAR SendBuffer[4096];
			StringCbPrintfW( SendBuffer, 4096, L"CONNECT %s:%d HTTP/1.1", m_Server, m_Port );
			m_pSocket->SendLine( SendBuffer );
			if( wcslen( m_ProxyUsername ) )
			{
				int len = 1029;
				BYTE strdec[258], strenc[1029];
				StringCbPrintfA( (LPSTR) strdec, 258, "%s:%s", CW2A(m_ProxyUsername), CW2A(m_ProxyPassword) );
				Base64Encode( strdec, strlen( (LPSTR) strdec ), (LPSTR) strenc, &len, ATL_BASE64_FLAG_NOCRLF );
				strenc[len] = 0;

				StringCbPrintfW( SendBuffer, 4096, L"Proxy-Authorization: Basic %s", strenc );
				m_pSocket->SendLine( SendBuffer );
			}
			m_pSocket->SendLine( L"" ); /* send a \r\n */


			unsigned char RecvBuffer[4096];
			err = -1;
			for( int i = 0; i < 4096; i++ )
			{
				if( m_pSocket->Recv( RecvBuffer+i, 1 ) <= 0 )
					break;
				if( i > 4 && RecvBuffer[i] == '\n' && RecvBuffer[i-1] == '\r' && RecvBuffer[i-2] == '\n' && RecvBuffer[i-3] == '\r' )
				{
					err = 0;
					break;
				}
			}
			if( !err )
			{
				err = -1;
				RecvBuffer[strlen( "HTTP/1.0 200 Connection established\r\n" )] = 0;
				if( !strcmp( (char *)RecvBuffer, "HTTP/1.0 200 Connection established\r\n" ) )
				{
					err = 0;
				}
			}
		}
	}
	else if( m_ProxyMethod == PROXY_METHOD_POLL )
	{
		err = -1;
	}

	if( !err )
	{
//		OutputDebugString( TEXT("CXMPP::AsyncConnect(): Connected to XMPP server...\n") );
		m_SendQueue.SetConnected();
		if( m_UseSSL )
			m_pSocket->StartTLS();
		DWORD arg = 1;
		ioctlsocket( m_pSocket->GetHandle(), FIONBIO, &arg );

		if( m_ConnectedHandler )
		{
			m_pMainWnd->Do( m_ConnectedHandler, &CComVariant("") );
		}

        xmlRegisterDefaultOutputCallbacks();

		m_bRestartParser = true;
		while( m_bRestartParser )
		{
//			OutputDebugString( _T("Resetting Parser\n") );
			m_nLevel = 0;
			m_CurrentStanza = L"";
			bufferreset();
			m_bRestartParser = false;
			m_namespaces.RemoveAll();

			xmlSAXHandlerPtr saxhdlr = new xmlSAXHandler;
			ZeroMemory( saxhdlr, sizeof( xmlSAXHandler ) );

			saxhdlr->startElement = CXMPP::startElementProc;
			saxhdlr->endElement = CXMPP::endElementProc;
			saxhdlr->characters = CXMPP::charactersProc;

			const int bufSize = 128 * 1024 + 1;
			timeval tv = { 0, 5000 }; // 5ms
			BYTE *pBytes = new BYTE[bufSize];
			xmlParserCtxtPtr ctxt = xmlCreatePushParserCtxt( saxhdlr, this, NULL, 0, NULL );

			bool bContinue = true;
			while( bContinue && !m_bRestartParser )
			{
				EnterCriticalSection( &m_csStartTLS );
				EnterCriticalSection( &m_csDisconnecting );
				if( m_pSocket )
				{
					int select = m_pSocket->Select( true, false, &tv );
					if( select == 1 )
					{
						int cbRead = m_pSocket->Recv( pBytes, bufSize - 1 );
						if( cbRead > 0 )
						{
#ifdef _DEBUG
							pBytes[cbRead] = 0;
							TCHAR dbgmsg[256 + 1];
							StringCbPrintf( dbgmsg, 256, TEXT("RECV (%d bytes): \t%s"), cbRead, CW2T(CUTF82W((char*)pBytes)) );
							StringCbCat( dbgmsg, 257, TEXT("\n") );
							OutputDebugString( dbgmsg );
#endif
							xmlParseChunk( ctxt, (const char *) pBytes, cbRead, 0 );
						}
						else if( cbRead == 0 )
						{
							bContinue = false;
						}
						else /* if( cbRead < 0 ) */
						{
							bContinue = false;
#ifdef _DEBUG
							TCHAR dbgmsg[256];
							StringCbPrintf( dbgmsg, 256, TEXT("Read error: 0x%x\n"), WSAGetLastError() );
							OutputDebugString( dbgmsg );
#endif
						}
					}
					else if( select == 0 )
					{
						/* nothing to see here, move along... */
					}
					else /* if ( select < 0 ) */
					{
						bContinue = false;
					}
				}
				else
				{
					bContinue = false;
				}
				LeaveCriticalSection( &m_csDisconnecting );
				LeaveCriticalSection( &m_csStartTLS );
			}

			delete pBytes;
			xmlFreeParserCtxt( ctxt );
			delete saxhdlr;
		}
		m_SendQueue.SetDisconnected();
	}
	else
	{
//		OutputDebugString( TEXT("CXMPP::AsyncConnect(): Could not connect to XMPP server!\n") );
	}
	Disconnect();
	return 0;
}
STDMETHODIMP CXMPP::StartTLS()
{
	DWORD ThreadID;
	CreateThread( NULL, 0, AsyncStartTLSProc, (void *)this, 0, &ThreadID );
	return S_OK;
}
DWORD __stdcall CXMPP::AsyncStartTLSProc( void *pThis )
{
	return ((CXMPP *) pThis)->AsyncStartTLS();
}
DWORD CXMPP::AsyncStartTLS()
{
	EnterCriticalSection( &m_csStartTLS );

	if( m_pSocket->StartTLS() )
	{
		m_bRestartParser = true;
		m_pMainWnd->Do( m_StartTLSSucceededHandler, &CComVariant("") );
	}
	else
		m_pMainWnd->Do( m_StartTLSFailedHandler, &CComVariant("") );

	LeaveCriticalSection( &m_csStartTLS );
	return 0;
}
STDMETHODIMP CXMPP::StartSC()
{
	DWORD ThreadID;
	CreateThread( NULL, 0, AsyncStartSCProc, (void *)this, 0, &ThreadID );
	return S_OK;
}
DWORD __stdcall CXMPP::AsyncStartSCProc( void *pThis )
{
	return ((CXMPP *) pThis)->AsyncStartSC();
}
DWORD CXMPP::AsyncStartSC()
{
	// use the TLS critical sections for now
	EnterCriticalSection( &m_csStartTLS );

	if( m_pSocket && m_pSocket->StartSC() )
	{
		m_bRestartParser = true;
		m_pMainWnd->Do( m_StartSCSucceededHandler, &CComVariant("") );
	}
	else
		m_pMainWnd->Do( m_StartSCFailedHandler, &CComVariant("") );

	LeaveCriticalSection( &m_csStartTLS );
	return 0;
}
STDMETHODIMP CXMPP::Disconnect()
{
	DWORD ThreadID;
	CreateThread( NULL, 0, AsyncDisconnectProc, (void *)this, 0, &ThreadID );
	return S_OK;
}
DWORD __stdcall CXMPP::AsyncDisconnectProc( void *pThis )
{
	return ((CXMPP *) pThis)->AsyncDisconnect();
}
DWORD CXMPP::AsyncDisconnect()
{
	/* Do not disconnect while starting TLS */
	EnterCriticalSection( &m_csStartTLS );
	EnterCriticalSection( &m_csDisconnecting );
	m_SendQueue.SetDisconnected();
	if( m_pSocket )
	{
//		OutputDebugString( TEXT("CXMPP::Disconnect(): Disconnecting XMPP connection...\n") );
		m_pSocket->Disconnect();
		delete m_pSocket;
		m_pSocket = NULL;

		if( m_DisconnectedHandler )
		{
			m_pMainWnd->Do( m_DisconnectedHandler, &CComVariant( "" ) );
		}

//		OutputDebugString( TEXT("CXMPP::Disconnect(): Disconnected from XMPP server...\n" ));
	}
	LeaveCriticalSection( &m_csDisconnecting );
	LeaveCriticalSection( &m_csStartTLS );
	return S_OK;
}
void CXMPP::AsyncSend( BYTE *data, DWORD len )
{
	m_SendQueue.AddData( m_pSocket, data, len );
}
STDMETHODIMP CXMPP::SendXML( VARIANT pDisp )
{
	if( pDisp.vt == VT_DISPATCH && pDisp.pdispVal )
	{
		MSXML2::IXMLDOMDocument *pXMLDoc;
		if( SUCCEEDED( pDisp.pdispVal->QueryInterface( IID_IXMLDOMDocument, (void **) &pXMLDoc ) ) )
		{
			BSTR xmlString;
			if( SUCCEEDED( pXMLDoc->get_xml( &xmlString ) ) )
			{
				/* Convert Unicode To UTF-8 */
				DWORD u8Len = UnicodeToUTF8( xmlString, wcslen( xmlString ), 0, 0 );
				LPSTR u8String = new CHAR[u8Len+1];
				UnicodeToUTF8( xmlString, wcslen( xmlString ), u8String, u8Len );
				SysFreeString( xmlString );
				u8String[u8Len] = 0;
			
				if( m_pSocket )
				{
					AsyncSend( (BYTE *) u8String, u8Len );
#ifndef _DEBUG
					TCHAR *debugmsg = new TCHAR[64+lstrlen(CW2T(CUTF82W(u8String)))];
					StringCbPrintf( debugmsg, 64+lstrlen(CW2T(CUTF82W(u8String))), _T("SENT (%d bytes): \t%s\n"), u8Len, CW2T(CUTF82W(u8String)) );
					OutputDebugString( debugmsg );
					delete debugmsg;
#endif
				}

				delete u8String;
			}
			else
			{
//				OutputDebugString( TEXT("CXMPP::SendXML(): Failed to extract XML data!\n") );
			}
		}
		else
		{
//			OutputDebugString( TEXT("CXMPP::SendXML(): Parameter is not a valid Msxml2.DOMDocument!\n") );
		}
	}
	return S_OK;
}
STDMETHODIMP CXMPP::SendText( BSTR strText )
{
	/* Convert Unicode To UTF-8 */
	DWORD u8Len = UnicodeToUTF8( strText, wcslen( strText ), 0, 0 );
	LPSTR szText = new CHAR[u8Len+1];
	UnicodeToUTF8( strText, wcslen( strText ), szText, u8Len );
	szText[u8Len] = 0;

	if( m_pSocket )
	{
        AsyncSend( (BYTE *) szText, u8Len );
#ifndef _DEBUG
		TCHAR *debugmsg = new TCHAR[64+lstrlen(CW2T(CUTF82W(szText)))];
		StringCbPrintf( debugmsg, 64+lstrlen(CW2T(CUTF82W(szText))), _T("SENT (%d bytes): \t%s\n"), u8Len, CW2T(CUTF82W(szText)) );
		OutputDebugString( debugmsg );
		delete debugmsg;
#endif
	}

	delete szText;
	return S_OK;
}

STDMETHODIMP CXMPP::put_ConnectedHandler( BSTR handler )
{
	/* = makes a copy */
	m_ConnectedHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_DisconnectedHandler( BSTR handler )
{
	m_DisconnectedHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_IQHandler( BSTR handler )
{
	m_IQHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_MessageHandler( BSTR handler )
{
	m_MessageHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_PresenceHandler( BSTR handler )
{
	m_PresenceHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_DocumentStartHandler( BSTR handler )
{
	m_DocumentStartHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_DocumentEndHandler( BSTR handler )
{
	m_DocumentEndHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_StreamHandler( BSTR handler )
{
	m_StreamHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_StartTLSSucceededHandler( BSTR handler )
{
	m_StartTLSSucceededHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_StartTLSFailedHandler( BSTR handler )
{
	m_StartTLSFailedHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_StartSCSucceededHandler( BSTR handler )
{
	m_StartSCSucceededHandler = handler;
	return S_OK;
}
STDMETHODIMP CXMPP::put_StartSCFailedHandler( BSTR handler )
{
	m_StartSCFailedHandler = handler;
	return S_OK;
}

STDMETHODIMP CXMPP::get_ConnectionIP( BSTR *strIP )
{
	if( m_pSocket )
        *strIP = m_pSocket->GetLocalAddress().copy();
	else
		*strIP = SysAllocString( L"" );
	return S_OK;
}
STDMETHODIMP CXMPP::SetProxyServer( BSTR server, USHORT port, BSTR username, BSTR password )
{
	m_ProxyServer = server;
	m_ProxyPort = port;
	m_ProxyUsername = username;
	m_ProxyPassword = password;
	return S_OK;
}
STDMETHODIMP CXMPP::SetProxyPollURL( BSTR pollURL )
{
	m_ProxyPollURL = pollURL;
	return S_OK;
}

STDMETHODIMP CXMPP::putDocumentLocator( /* [in] */ ISAXLocator __RPC_FAR *pLocator )
{
	return S_OK;
}
STDMETHODIMP CXMPP::startDocument()
{
	return S_OK;
}
STDMETHODIMP CXMPP::endDocument()
{
	return S_OK;
}
STDMETHODIMP CXMPP::startPrefixMapping( /* [in] */ wchar_t __RPC_FAR *pwchPrefix, /* [in] */ int cchPrefix, /* [in] */ wchar_t __RPC_FAR *pwchUri, /* [in] */ int cchUri )
{
	return S_OK;
}
STDMETHODIMP CXMPP::endPrefixMapping( /* [in] */ wchar_t __RPC_FAR *pwchPrefix, /* [in] */ int cchPrefix)
{
	return S_OK;
}
void CXMPP::startElementProc( void * ctx, const xmlChar *name, const xmlChar** atts )
{
	((CXMPP*)ctx)->startElement( L"", 0, L"", 0, CUTF82W( name ), wcslen( CUTF82W( name ) ), &CAttributes( atts ) );
}
//STDMETHODIMP CXMPP::startElement( /* [in] */ wchar_t __RPC_FAR *pwchNamespaceUri, /* [in] */ int cchNamespaceUri, /* [in] */ wchar_t __RPC_FAR *pwchLocalName, /* [in] */ int cchLocalName, /* [in] */ wchar_t __RPC_FAR *pwchRawName, /* [in] */ int cchRawName, /* [in] */ ISAXAttributes __RPC_FAR *pAttributes )
STDMETHODIMP CXMPP::startElement( /* [in] */ wchar_t __RPC_FAR *pwchNamespaceUri, /* [in] */ int cchNamespaceUri, /* [in] */ wchar_t __RPC_FAR *pwchLocalName, /* [in] */ int cchLocalName, /* [in] */ wchar_t __RPC_FAR *pwchRawName, /* [in] */ int cchRawName, /* [in] */ CAttributes __RPC_FAR *pAttributes )
{
	CComBSTR bstrNamespaceUri = CComBSTR( cchNamespaceUri, pwchNamespaceUri );
	CComBSTR bstrLocalName = CComBSTR( cchLocalName, pwchLocalName );
	CComBSTR bstrRawName = CComBSTR( cchRawName, pwchRawName );

	/* stream:stream */
	if( !wcscmp( bstrRawName, L"stream:stream" ) )
	{
		CComBSTR XMLFragment = L"";
		RecordElementBegin( XMLFragment, bstrNamespaceUri, bstrLocalName, bstrRawName, pAttributes );
		m_pMainWnd->Do( m_DocumentStartHandler, &CComVariant(XMLFragment) );
	}

	/* new stanza */
	else if( !wcscmp( m_CurrentStanza, L"" ) )
	{
		bufferreset();
		RecordElementBegin( bstrNamespaceUri, bstrLocalName, bstrRawName, pAttributes );
		m_CurrentStanza = bstrRawName.Copy();
	}

	/* nested */
	else if( !wcscmp( bstrRawName, m_CurrentStanza ) )
	{
		m_nLevel++;
		RecordElementBegin( bstrNamespaceUri, bstrLocalName, bstrRawName, pAttributes );
	}
	
	/* we're currently recording */
	else
	{
		RecordElementBegin( bstrNamespaceUri, bstrLocalName, bstrRawName, pAttributes );
	}

	return S_OK;
}
void CXMPP::endElementProc( void * ctx, const xmlChar *name )
{
	((CXMPP*)ctx)->endElement( L"", 0, L"", 0, CUTF82W( name ), wcslen( CUTF82W( name ) ) );
}
STDMETHODIMP CXMPP::endElement( /* [in] */ wchar_t __RPC_FAR *pwchNamespaceUri, /* [in] */ int cchNamespaceUri, /* [in] */ wchar_t __RPC_FAR *pwchLocalName, /* [in] */ int cchLocalName, /* [in] */ wchar_t __RPC_FAR *pwchRawName, /* [in] */ int cchRawName )
{
	CComBSTR bstrRawName = CComBSTR( cchRawName, pwchRawName );

	/* stream:stream */
	if( !wcscmp( bstrRawName, L"stream:stream" ) )
	{
		CComBSTR XMLFragment = L"</";
		XMLFragment += pwchRawName;
		XMLFragment += L">";
		m_pMainWnd->Do( m_DocumentEndHandler, &CComVariant(XMLFragment) );
	}
	/* found our current stanza */
	else if( !wcscmp( bstrRawName, m_CurrentStanza ) )
	{
		/* nested */
		if( m_nLevel > 0  )
		{
			bufferappendend( pwchRawName, cchRawName );
			m_nLevel--;
		}
		else
		{
			bufferappendend( pwchRawName, cchRawName );
	
			CComPtr<MSXML2::IXMLDOMDocument> pXMLDoc;
			pXMLDoc.CoCreateInstance( CLSID_DOMDocument );
			pXMLDoc->put_async( FALSE );			
			pXMLDoc->put_validateOnParse( FALSE );
			pXMLDoc->put_resolveExternals( FALSE );

			VARIANT_BOOL bSuccess;
			bufferappendnul();
			if( SUCCEEDED( pXMLDoc->loadXML( xmlbuffer, &bSuccess ) ) && bSuccess )
			{
				CComBSTR Handler;
				if( !wcscmp( bstrRawName, L"iq" ) )
					Handler = m_IQHandler;
				else if( !wcscmp( bstrRawName, L"message" ) )
					Handler = m_MessageHandler;
				else if( !wcscmp( bstrRawName, L"presence" ) )
					Handler = m_PresenceHandler;
				else
					Handler = m_StreamHandler;

                m_pMainWnd->Do( Handler, &CComVariant( CComQIPtr<IDispatch>( pXMLDoc ) ) );
				if( !wcscmp( bstrRawName, L"success" ) )
				{
					m_bRestartParser = true;
				}
			}
			else
			{
				MSXML2::IXMLDOMParseError *errorObj;
				pXMLDoc->get_parseError( &errorObj );
				BSTR bstrReason;
				errorObj->get_reason( &bstrReason );
//				OutputDebugString( TEXT( "xml parse error: " ) );
//				OutputDebugString( CW2T( bstrReason ) );
				errorObj->Release();
				Disconnect();
			}

			m_CurrentStanza = L"";
		}
	}
	else
	{
		bufferappendend( pwchRawName, cchRawName );
	}
	return S_OK;
}
void CXMPP::charactersProc( void * ctx, const xmlChar * ch, int len )
{
	/*
	 * Copy the UTF-8 characters to a new buffer
	 */
	char *buffer = new char[len+1];
	memcpy( buffer, ch, len );
	buffer[len] = 0;

	/* 
	 * Convert the buffer to UTF-16 and call the characters parse function
	 */
	CComBSTR chars( len, CUTF82W( buffer ) );
	((CXMPP*)ctx)->characters( chars, wcslen( chars ) );

	/*
	 * Clean up
	 */
	delete buffer;
}
STDMETHODIMP CXMPP::characters( /* [in] */ wchar_t __RPC_FAR *pwchChars, /* [in] */ int cchChars )
{
	for( int i = 0; i < cchChars; i++ )
	{
		if( pwchChars[i] == L'<' )
			bufferappendlt();
		else if( pwchChars[i] == L'>' )
			bufferappendgt();
		else if( pwchChars[i] == L'&' )
			bufferappendamp();
		else 
			bufferappendchar( pwchChars[i] );
	}
	return S_OK;
}
STDMETHODIMP CXMPP::ignorableWhitespace( /* [in] */ wchar_t __RPC_FAR *pwchChars, /* [in] */ int cchChars )
{
	return S_OK;
}
STDMETHODIMP CXMPP::processingInstruction( /* [in] */ wchar_t __RPC_FAR *pwchTarget, /* [in] */ int cchTarget, /* [in] */ wchar_t __RPC_FAR *pwchData, /* [in] */ int cchData )
{
	return S_OK;
}    
STDMETHODIMP CXMPP::skippedEntity( /* [in] */ wchar_t __RPC_FAR *pwchName, /* [in] */ int cchName )
{
	return S_OK;
}

STDMETHODIMP CXMPP::error( /* [in] */ ISAXLocator __RPC_FAR *pLocator, /* [in] */ unsigned short * pwchErrorMessage, /* [in] */ HRESULT errCode )
{
//	OutputDebugString( TEXT("Parser stopped:\t") );
//	OutputDebugString( CW2T(pwchErrorMessage) );
	return S_OK;
}
STDMETHODIMP CXMPP::fatalError( /* [in] */ ISAXLocator __RPC_FAR *pLocator, /* [in] */ unsigned short * pwchErrorMessage, /* [in] */ HRESULT errCode )
{
//	OutputDebugString( TEXT("Parser stopped:\t") );
//	OutputDebugString( CW2T(pwchErrorMessage) );
	return S_OK;
}
STDMETHODIMP CXMPP::ignorableWarning( /* [in] */ ISAXLocator __RPC_FAR *pLocator, /* [in] */ unsigned short * pwchErrorMessage, /* [in] */ HRESULT errCode )
{
//	OutputDebugString( TEXT("Parser warning:\t") );
//	OutputDebugString( CW2T(pwchErrorMessage) );
	return S_OK;
}

//void CXMPP::RecordElementBegin( CComBSTR &bstrRecord, const CComBSTR &bstrNamespaceUri, const CComBSTR &bstrLocalName, const CComBSTR &bstrRawName, ISAXAttributes *pAttributes )
void CXMPP::RecordElementBegin( const CComBSTR &bstrNamespaceUri, const CComBSTR &bstrLocalName, const CComBSTR &bstrRawName, CAttributes *pAttributes )
{
	bufferappendchar( L'<' );
	bufferappendstring( bstrRawName, bstrRawName.Length() );

	int nAttributes;
	pAttributes->getLength( &nAttributes );
	for( int i = 0; i < nAttributes; i++ )
	{
		int cchQName;
		wchar_t *pwchQName;
		pAttributes->getQName( i, &pwchQName, &cchQName );

		if( cchQName )
		{
			int cchValue;
			wchar_t *pwchValue;
			pAttributes->getValue( i, &pwchValue, &cchValue );

			bufferappendchar( L' ' );
			bufferappendstring( pwchQName, cchQName );
			bufferappendchar( L'=' );
			bufferappendchar( L'\"' );

			for( int i = 0; i < cchValue; i++ )
			{
				if( pwchValue[i] == L'<' )
					bufferappendlt();
				/*else if( pwchValue[i] == L'&' )
					bufferappendamp();*/
				else if( pwchValue[i] == L'\"' )
					bufferappendquot();
				else if( pwchValue[i] == L'>' )
					bufferappendgt();
				else 
					bufferappendchar( pwchValue[i] );
			}
			bufferappendchar( L'\"' );
			SysFreeString( pwchQName );
			SysFreeString( pwchValue );
		}
	}
	
	if( wcsstr( bstrRawName, L":" ) )
	{
		CComBSTR bstrNamespace = L"xmlns:";
		bstrNamespace.Append( bstrRawName, wcsstr( bstrRawName, L":" ) - (BSTR) bstrRawName );

		bool bNsUriDefined = false;

		for( int i = 0; i < nAttributes; i++ )
		{
			int cchQName;
			wchar_t *pwchQName;
			pAttributes->getQName( i, &pwchQName, &cchQName );
			CComBSTR bstrQName = CComBSTR( cchQName, pwchQName );
			SysFreeString( pwchQName );

			if( !wcscmp( bstrNamespace, bstrQName ) )
			{
				wchar_t *pwchValue;
				int cchValue = 0;
				pAttributes->getValue( i, &pwchValue, &cchValue );
				
				m_namespaces[bstrNamespace] = CComBSTR( cchValue, pwchValue );
				bNsUriDefined = true;
			}
		}

		if( !bNsUriDefined )
        {
			bufferappendchar( L' ' );
			bufferappendstring( bstrNamespace, bstrNamespace.Length() );
			bufferappendchar( L'=' );
			bufferappendchar( L'\"' );
			bufferappendstring( m_namespaces[bstrNamespace], m_namespaces[bstrNamespace].Length() );
			bufferappendchar( L'\"' );
        }
	}
	bufferappendchar( L'>' );
}
void CXMPP::RecordElementBegin( CComBSTR &bstrRecord, const CComBSTR &bstrNamespaceUri, const CComBSTR &bstrLocalName, const CComBSTR &bstrRawName, CAttributes *pAttributes )
{
	bstrRecord += L"<";
	bstrRecord += bstrRawName;

	int nAttributes;
	pAttributes->getLength( &nAttributes );
	for( int i = 0; i < nAttributes; i++ )
	{
		int cchQName;
		wchar_t *pwchQName;
		pAttributes->getQName( i, &pwchQName, &cchQName );

		if( cchQName )
		{
			int cchValue;
			wchar_t *pwchValue;
			pAttributes->getValue( i, &pwchValue, &cchValue );

			bstrRecord += L" ";
			bstrRecord.Append( pwchQName, cchQName );
			bstrRecord += L"=\"";

			for( int i = 0; i < cchValue; i++ )
			{
				if( pwchValue[i] == L'<' )
					bstrRecord += L"&lt;";
				else if( pwchValue[i] == L'&' )
					bstrRecord += L"&amp;";
				else if( pwchValue[i] == L'\"' )
					bstrRecord += L"&quot;";
				else if( pwchValue[i] == L'>' )
					bstrRecord += L"&gt;";
				else 
					bstrRecord.Append( &pwchValue[i], 1 );
			}
			bstrRecord += L"\"";
			SysFreeString( pwchQName );
			SysFreeString( pwchValue );
		}
	}
	
	if( wcsstr( bstrRawName, L":" ) )
	{
		CComBSTR bstrNamespace = L"xmlns:";
		bstrNamespace.Append( bstrRawName, wcsstr( bstrRawName, L":" ) - (BSTR) bstrRawName );

		bool bNsUriDefined = false;

		for( int i = 0; i < nAttributes; i++ )
		{
			int cchQName;
			wchar_t *pwchQName;
			pAttributes->getQName( i, &pwchQName, &cchQName );
			CComBSTR bstrQName = CComBSTR( cchQName, pwchQName );
			SysFreeString( pwchQName );

			if( !wcscmp( bstrNamespace, bstrQName ) )
			{
				wchar_t *pwchValue;
				int cchValue = 0;
				pAttributes->getValue( i, &pwchValue, &cchValue );
				
				m_namespaces[bstrNamespace] = CComBSTR( cchValue, pwchValue );
				bNsUriDefined = true;
			}
		}

		if( !bNsUriDefined )
        {
			bstrRecord += L" ";
			bstrRecord += bstrNamespace;
			bstrRecord += L"=\"";
			bstrRecord += m_namespaces[bstrNamespace];
			bstrRecord += L"\"";
        }
	}
	bstrRecord += L">";
}