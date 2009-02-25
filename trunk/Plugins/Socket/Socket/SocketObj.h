#pragma once

#include <iostream>

using namespace std;

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class SocketJSObject;

class Socket
{
	static bool notInitialized;
	SocketJSObject* jsObjectContainer;
	bool shouldBeRunning;
	BIO * bio;
	SSL* ssl;
	SSL_CTX * ctx;
	BIO * ssl_bio;

public:

	Socket(SocketJSObject* _jsObjectContainer);

	~Socket();

	bool Run();

	bool Connect(const string& hostname, const string & port);

	bool startTLS();

	void Write(const string & data);

	void Read(string & readBuffer);

	void Disconnect();
};
