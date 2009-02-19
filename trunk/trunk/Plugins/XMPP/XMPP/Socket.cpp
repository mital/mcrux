#include "StdAfx.h"
#include "Socket.h"

#include <sys/types.h>

bool Socket::notInitialized = true;

Socket::Socket()
: bio(NULL),
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
	return true;
}


void Socket::Write(const string & data)
{
	//BIO* bio_to_write = bio;
	//if(ssl_bio)
	//{
	//	bio_to_write = ssl_bio;
	//}
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
			bio = BIO_push(ssl_bio, bio);
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
	
}