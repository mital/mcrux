#include "StdAfx.h"
#include "Socket.h"
#include <process.h>

#include <sys/types.h>

#include "XMPPJSObject.h"


bool Socket::notInitialized = true;

void StartSocketThread(void * socketVoid)
{
	try
	{
		Socket * socket = (Socket *) socketVoid;
		if(socket->Run())
		{
			//::MessageBoxA(0, "Run returned true", "socket thread", MB_OK);
		}
		else
		{
			//::MessageBoxA(0, "Run returned false", "socket thread", MB_OK);
		}
	}
	catch(...)
	{
	}
}

Socket::Socket(XMPPJSObject* _jsObjectContainer)
: jsObjectContainer(_jsObjectContainer),
  shouldBeRunning(false),
  bio(NULL),
  ssl(NULL),
  ctx(NULL),
  ssl_bio(NULL)
{
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
}

bool Socket::Connect(const string& hostname, const string & port)
{
	if(bio)
	{
		BIO_free_all(bio);
		bio = NULL;
	}


	bio = BIO_new_connect((char*)hostname.c_str());
	BIO_set_nbio(bio, 1);
	if (!bio)
	{
		return false;
	}

	BIO_set_conn_port(bio, port.c_str());

	if(BIO_do_connect(bio) <= 0)
	{
		//TODO: implement some way of error message showing
		//ERR_print_errors_fp(stderr);
		BIO_free_all(bio);
		return false;
	}
	shouldBeRunning = true;

	_beginthread(StartSocketThread, 0, this);
	return true;
}


void Socket::Write(const string & data)
{
	int writtenByteCount = BIO_write(bio, data.c_str(), (int)data.size());
}

void Socket::Read(string & readBuffer)
{
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
}


bool Socket::startTLS_SSL()
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
		if (!readBuffer.empty()
			//&& (stanzaHandler)
			)
		{
			jsObjectContainer->callStanzaHandler(readBuffer);
			readBuffer = "";
		}
	}
	return false;
}
