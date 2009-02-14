#pragma once

#define PROXY_METHOD_DONTUSE 0
#define PROXY_METHOD_CONNECT 1
#define PROXY_METHOD_POLL    3

//class CMainWnd;
class CSocket;
class CAttributes;

class CSendBuffer
{
public:
	CSendBuffer( CSocket *pSocket, BYTE *pBuffer, DWORD bufLen );
	~CSendBuffer();
	DWORD Send();
private:
	CSocket *m_pSocket;
	BYTE *m_pBuffer;
	DWORD m_Len;
};

class CSendQueue
{
private:
	HANDLE m_hDataAvailable;
	bool m_bConnected;
	CRITICAL_SECTION m_csAccessingQueue;
	HANDLE m_hThread;
public:
	CSendQueue();
	~CSendQueue();
	void AddData( CSocket* pSocket, BYTE *pData, DWORD Len );
	DWORD SendData();

	void SetConnected();
	void SetDisconnected();

	static DWORD __stdcall SendQueueProc( void *pThis );
	void CSendQueue::WaitForData();
private:
	CAtlList<CSendBuffer*> m_Buffers;
};

class CXMPP :
	public CComObjectRootEx< CComSingleThreadModel >,
	public IDispatchImpl< IXMPP >
{
private:
	CRITICAL_SECTION m_csDisconnecting;
	CRITICAL_SECTION m_csStartTLS;

	CComBSTR  m_ConnectedHandler;
	CComBSTR  m_DisconnectedHandler;
	CComBSTR  m_IQHandler;
	CComBSTR  m_MessageHandler;
	CComBSTR  m_PresenceHandler;
	CComBSTR  m_DocumentStartHandler;
	CComBSTR  m_DocumentEndHandler;
	CComBSTR  m_StreamHandler;
	CComBSTR  m_StartTLSSucceededHandler;
	CComBSTR  m_StartTLSFailedHandler;
	CComBSTR  m_StartSCSucceededHandler;
	CComBSTR  m_StartSCFailedHandler;

	CSocket  *m_pSocket;
	CSendQueue m_SendQueue;
	//CMainWnd *m_pMainWnd;

	CComBSTR  m_Server;
	USHORT    m_Port;
	BOOL      m_UseSSL;
	
	DWORD     m_ProxyMethod;
	CComBSTR  m_ProxyPollURL;
	CComBSTR  m_ProxyServer;
	USHORT    m_ProxyPort;
	CComBSTR  m_ProxyUsername;
	CComBSTR  m_ProxyPassword;

	//CComBSTR	m_XMLBuffer;
	wchar_t     *xmlbuffer;
	wchar_t     *xmlbufferp;
	DWORD       xmlbufferleft;
	CComBSTR	m_CurrentStanza;
	int			m_nLevel;
	BOOL        m_bRestartParser;
	bool        m_bFirstRead;

	CAtlMap< CComBSTR, CComBSTR> m_namespaces;

	void bufferappendlt()
	{
		buffergrow( 4 );
		*xmlbufferp++ = L'&';
		*xmlbufferp++ = L'l';
		*xmlbufferp++ = L't';
		*xmlbufferp++ = L';';
		xmlbufferleft -= 4;
	}
	void bufferappendgt()
	{
		buffergrow( 4 );
		*xmlbufferp++ = L'&';
		*xmlbufferp++ = L'g';
		*xmlbufferp++ = L't';
		*xmlbufferp++ = L';';
		xmlbufferleft -= 4;
	}
	void bufferappendquot()
	{
		buffergrow( 6 );
		*xmlbufferp++ = L'&';
		*xmlbufferp++ = L'q';
		*xmlbufferp++ = L'u';
		*xmlbufferp++ = L'o';
		*xmlbufferp++ = L't';
		*xmlbufferp++ = L';';
		xmlbufferleft -= 6;
	}
	void bufferappendamp()
	{
		buffergrow( 5 );
		*xmlbufferp++ = L'&';
		*xmlbufferp++ = L'a';
		*xmlbufferp++ = L'm';
		*xmlbufferp++ = L'p';
		*xmlbufferp++ = L';';
		xmlbufferleft -= 5;
	}
	void bufferappendchar( wchar_t c )
	{
		buffergrow( 1 );
		*xmlbufferp++ = c;
		xmlbufferleft--;
	}
	void bufferappendnul()
	{
		buffergrow( 1 );
		*xmlbufferp++ = 0;
		xmlbufferleft--;
	}
	void bufferappendstring( wchar_t *str, int len )
	{
		buffergrow( len );
		memcpy( xmlbufferp, str, len * sizeof(wchar_t) );
		xmlbufferp += len;
		xmlbufferleft -= len;
	}
	void bufferappendend( wchar_t* str, int len )
	{
		buffergrow( 2 + len + 1 );
		*xmlbufferp++ = L'<';
		*xmlbufferp++ = L'/';
		memcpy( xmlbufferp, str, len * sizeof(wchar_t) );
		xmlbufferp += len;
		*xmlbufferp++ = L'>';
		xmlbufferleft -= 2 + len + 1;
	}
	void bufferreset()
	{
		xmlbufferleft += (xmlbufferp - xmlbuffer);
		xmlbufferp = xmlbuffer;
	}
	void buffergrow( DWORD size )
	{
		if( xmlbufferleft < size )
		{
			DWORD oldSize = ( xmlbufferp - xmlbuffer ) + xmlbufferleft;
			wchar_t *p = new wchar_t[ (size > oldSize) ? oldSize + size : oldSize * 2 ];
			memcpy( p, xmlbuffer, (xmlbufferp - xmlbuffer) * sizeof(wchar_t) );
			xmlbufferleft += (size > oldSize) ? size : oldSize;
			xmlbufferp = p + (xmlbufferp - xmlbuffer);
			delete xmlbuffer;
			xmlbuffer = p;
		}
	}
public:
	CXMPP();
	virtual ~CXMPP();

//	void RecordElementBegin( CComBSTR &bstrRecord, const CComBSTR &bstrNamespaceUri, const CComBSTR &bstrLocalName, const CComBSTR &bstrRawName, ISAXAttributes *pAttributes );
	void RecordElementBegin( const CComBSTR &bstrNamespaceUri, const CComBSTR &bstrLocalName, const CComBSTR &bstrRawName, CAttributes *pAttributes );
	void RecordElementBegin( CComBSTR &bstrRecord, const CComBSTR &bstrNamespaceUri, const CComBSTR &bstrLocalName, const CComBSTR &bstrRawName, CAttributes *pAttributes );
	void SetServer( BSTR server );
	void SetPort( USHORT port );
	void UseSSL( BOOL b );
	void AsyncSend( BYTE *data, DWORD len );

	/* IUnknown implementation */
BEGIN_COM_MAP(CXMPP)
	COM_INTERFACE_ENTRY( IDispatch )
	COM_INTERFACE_ENTRY( IXMPP )
END_COM_MAP()

	/* IXMPP implementation */
	STDMETHOD(SetMainWnd)( void *pMainWnd );
	STDMETHOD(Connect)( BSTR server, USHORT port, BOOL useSSL = FALSE, DWORD proxyMethod = 0 );
	static DWORD __stdcall AsyncConnectProc( void *pThis );
	//void ProcessNode( xmlTextReaderPtr p );
	DWORD AsyncConnect();

	STDMETHOD(StartTLS)();
	static DWORD __stdcall AsyncStartTLSProc( void *pThis );
	DWORD AsyncStartTLS();

	STDMETHOD(StartSC)();
	static DWORD __stdcall AsyncStartSCProc( void *pThis );
	DWORD AsyncStartSC();

	STDMETHOD(Disconnect)();
	static DWORD __stdcall AsyncDisconnectProc( void *pThis );
	DWORD AsyncDisconnect();
	
	STDMETHOD(SendXML)( VARIANT pDisp );
	STDMETHOD(SendText)( BSTR strText );

	STDMETHOD(put_ConnectedHandler)( BSTR handler );
	STDMETHOD(put_DisconnectedHandler)( BSTR handler );
	STDMETHOD(put_IQHandler)( BSTR handler );
	STDMETHOD(put_MessageHandler)( BSTR handler );
	STDMETHOD(put_PresenceHandler)( BSTR handler );
	STDMETHOD(put_DocumentStartHandler)( BSTR handler );
	STDMETHOD(put_DocumentEndHandler)( BSTR handler );
	STDMETHOD(put_StreamHandler)( BSTR handler );
	STDMETHOD(put_StartTLSSucceededHandler)( BSTR handler );
	STDMETHOD(put_StartTLSFailedHandler)( BSTR handler );
	STDMETHOD(put_StartSCSucceededHandler)( BSTR handler );
	STDMETHOD(put_StartSCFailedHandler)( BSTR handler );

	STDMETHOD(get_ConnectionIP)( BSTR *strIP );

	STDMETHOD(SetProxyServer)( BSTR server, USHORT port, BSTR username, BSTR password );
	STDMETHOD(SetProxyPollURL)( BSTR pollURL );

	/* ISAXContentHandler implementation */
    STDMETHOD(putDocumentLocator)( /* [in] */ ISAXLocator __RPC_FAR *pLocator );
    STDMETHOD(startDocument)();
    STDMETHOD(endDocument)();
    STDMETHOD(startPrefixMapping)( /* [in] */ wchar_t __RPC_FAR *pwchPrefix, /* [in] */ int cchPrefix, /* [in] */ wchar_t __RPC_FAR *pwchUri, /* [in] */ int cchUri );
    STDMETHOD(endPrefixMapping)( /* [in] */ wchar_t __RPC_FAR *pwchPrefix, /* [in] */ int cchPrefix);

	static void startElementProc( void * ctx, const xmlChar * name, const xmlChar ** atts );
//	STDMETHOD(startElement)( /* [in] */ wchar_t __RPC_FAR *pwchNamespaceUri, /* [in] */ int cchNamespaceUri, /* [in] */ wchar_t __RPC_FAR *pwchLocalName, /* [in] */ int cchLocalName, /* [in] */ wchar_t __RPC_FAR *pwchRawName, /* [in] */ int cchRawName, /* [in] */ ISAXAttributes __RPC_FAR *pAttributes );
	STDMETHOD(startElement)( /* [in] */ wchar_t __RPC_FAR *pwchNamespaceUri, /* [in] */ int cchNamespaceUri, /* [in] */ wchar_t __RPC_FAR *pwchLocalName, /* [in] */ int cchLocalName, /* [in] */ wchar_t __RPC_FAR *pwchRawName, /* [in] */ int cchRawName, /* [in] */ CAttributes __RPC_FAR *pAttributes );

	static void endElementProc( void * ctx, const xmlChar * name );
    STDMETHOD(endElement)( /* [in] */ wchar_t __RPC_FAR *pwchNamespaceUri, /* [in] */ int cchNamespaceUri, /* [in] */ wchar_t __RPC_FAR *pwchLocalName, /* [in] */ int cchLocalName, /* [in] */ wchar_t __RPC_FAR *pwchRawName, /* [in] */ int cchRawName );

	static void charactersProc( void * ctx, const xmlChar * ch, int len );
    STDMETHOD(characters)( /* [in] */ wchar_t __RPC_FAR *pwchChars, /* [in] */ int cchChars );

	STDMETHOD(ignorableWhitespace)( /* [in] */ wchar_t __RPC_FAR *pwchChars, /* [in] */ int cchChars );
    STDMETHOD(processingInstruction)( /* [in] */ wchar_t __RPC_FAR *pwchTarget, /* [in] */ int cchTarget, /* [in] */ wchar_t __RPC_FAR *pwchData, /* [in] */ int cchData );    
    STDMETHOD(skippedEntity)( /* [in] */ wchar_t __RPC_FAR *pwchName, /* [in] */ int cchName );

	/* ISAXErrorHandler */
	STDMETHOD(error)( /* [in] */ ISAXLocator __RPC_FAR *pLocator, /* [in] */ unsigned short * pwchErrorMessage, /* [in] */ HRESULT errCode );
    STDMETHOD(fatalError)( /* [in] */ ISAXLocator __RPC_FAR *pLocator, /* [in] */ unsigned short * pwchErrorMessage, /* [in] */ HRESULT errCode );
    STDMETHOD(ignorableWarning)( /* [in] */ ISAXLocator __RPC_FAR *pLocator, /* [in] */ unsigned short * pwchErrorMessage, /* [in] */ HRESULT errCode );
};
