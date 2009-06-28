#include "StdAfx.h"
#include "SocketObj.h"
#include <process.h>
#include <winsock.h>
#include <sys/types.h>

#include "SocketJSObject.h"


bool Socket::notInitialized = true;

void StartSocketThread(void * socketVoid)
{
	try
	{
		Socket * socket = (Socket *) socketVoid;
		if(socket->Connect())
		{
			socket->onConnectComplete(true);
			if(socket->Run())
			{
				//::MessageBoxA(0, "Run returned true", "socket thread", MB_OK);
			}
			else
			{
				//::MessageBoxA(0, "Run returned false", "socket thread", MB_OK);
			}
		}
		else
		{
			socket->onConnectComplete(false);
		}
	}
	catch(...)
	{
	}
}

Socket::Socket(SocketJSObject* _jsObjectContainer)
: jsObjectContainer(_jsObjectContainer),
  shouldBeRunning(false),
  hostname(""),
  port(""),
  bio(NULL),
  ssl(NULL),
  ctx(NULL),
  ssl_bio(NULL)
{
	InitializeCriticalSection( &m_csReading );
	InitializeCriticalSection( &m_csWriting );

	if(notInitialized)
	{
		ERR_load_BIO_strings();
		SSL_load_error_strings();
		OpenSSL_add_all_algorithms();
		notInitialized = false;
	}
}

Socket::~Socket()
{
	shouldBeRunning = false;
	DeleteCriticalSection( &m_csReading );
	DeleteCriticalSection( &m_csWriting );
}


void Socket::setConnectParams(const string& _hostname, const string& _port)
{
	hostname = _hostname;
	port = _port;
}


bool Socket::Connect()
{
	EnterCriticalSection( &m_csReading );
	EnterCriticalSection( &m_csWriting );

	if (hostname.size() < 0)
	{
		LeaveCriticalSection( &m_csReading );
		LeaveCriticalSection( &m_csWriting );
		return false;
	}

	if(bio)
	{
		BIO_free_all(bio);
		bio = NULL;
	}

	bio = BIO_new_connect((char*)hostname.c_str());
	
	if (!bio)
	{
		LeaveCriticalSection( &m_csReading );
		LeaveCriticalSection( &m_csWriting );
		return false;
	}

	BIO_set_nbio(bio, 1);

	if(!BIO_set_conn_port(bio, port.c_str()))
	{
		LeaveCriticalSection( &m_csReading );
		LeaveCriticalSection( &m_csWriting );
		return false;
	}

	long retVal = BIO_do_connect(bio);

	if(retVal <= 0)
	{
		struct sockaddr sad;
		int l = sizeof(sad);
		if(getpeername(bio->num, &sad, &l) != 0)
		{
			if (!BIO_should_retry(bio))
			{
				LeaveCriticalSection( &m_csReading );
				LeaveCriticalSection( &m_csWriting );
				return false;
			}

			//TODO: implement some way of error message showing
			//const char * error = ERR_func_error_string(ERR_get_error());
			BIO_free_all(bio);

			LeaveCriticalSection( &m_csReading );
			LeaveCriticalSection( &m_csWriting );
			return false;
		}
	}
	shouldBeRunning = true;

	LeaveCriticalSection( &m_csReading );
	LeaveCriticalSection( &m_csWriting );
	return true;
}

void Socket::onConnectComplete(bool bConnected)
{
	jsObjectContainer->onConnectComplete(hostname, port, bConnected);
}


bool Socket::Write(const string & data)
{
	EnterCriticalSection( &m_csWriting );

	int writtenByteCount = BIO_write(bio, data.c_str(), (int)data.size());
	char buf[10];
	_itoa_s(writtenByteCount, buf, 10, 10);
	::MessageBoxA(0, buf, "Bytes written", MB_OK);

	LeaveCriticalSection( &m_csWriting );
	return true;
}


void Socket::Read(string & readBuffer)
{
	EnterCriticalSection( &m_csReading );

	char buf[1024];
	int readBytes;
	for(;;)
	{
		readBytes = BIO_read(bio, buf, 1023);
		if(readBytes <= 0)
		{
			break;
		}
		buf[readBytes] = 0;
		readBuffer += buf;
	}

	LeaveCriticalSection( &m_csReading );
}


bool Socket::startTLS()
{
	if(bio && !ssl && !ctx)
	{
		ctx = SSL_CTX_new(SSLv23_client_method());
		if(ctx)
		{
			//    /* Load the trust store */
			//
			//    if(! SSL_CTX_load_verify_locations(ctx, "TrustStore.pem", NULL))
			//    {
			//        ERR_print_errors_fp(stderr);
			//        SSL_CTX_free(ctx);
			//        return 0;
			//    }

			ssl = SSL_new(ctx);
			ssl_bio = BIO_new_ssl_connect(ctx);
			int i = BIO_do_handshake(bio);
			bio = BIO_push(bio, ssl_bio);
		}
	}

	return false;
}


bool startCompression()
{
	BIO * sbio = BIO_new(BIO_f_ssl());
	BIO * bbio = BIO_new(BIO_f_base64());
	return true;
}


void Socket::Disconnect()
{
	shouldBeRunning = false;
	// TODO: cleanup the BIOs
	BIO_free_all(bio);
	// store thread id and wait for thread to exit.
}


bool Socket::Run()
{
	string readBuffer;
	while(shouldBeRunning)
	{
		readBuffer = "";
		Read(readBuffer);
		if (readBuffer.size() > 0)
		{
			jsObjectContainer->handleReadData(readBuffer);
		}
	}
	return true;
}
