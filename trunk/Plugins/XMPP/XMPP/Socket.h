#pragma once

#include <iostream>

using namespace std;

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


class Socket
{
	static bool notInitialized;
	BIO * bio;
	SSL* ssl;
	SSL_CTX * ctx;
	BIO * ssl_bio;

public:

	Socket();
	~Socket();

	bool Connect(const string& hostname, const string & port);

	bool startTLS_SSL();

	void Write(const string & data);

	void Read(string & readBuffer);

	void Disconnect();
};
