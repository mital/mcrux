#pragma once

#include <iostream>

using namespace std;

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class SocketJSObject;
void StartSocketThread(void * socketVoid);

class Socket
{
	CRITICAL_SECTION m_csReading;
	CRITICAL_SECTION m_csWriting;

	static bool notInitialized;
	SocketJSObject* jsObjectContainer;
	bool shouldBeRunning;
	string hostname;
	string port;
	BIO * bio;
	SSL* ssl;
	SSL_CTX * ctx;
	BIO * ssl_bio;

public:

	Socket(SocketJSObject* _jsObjectContainer);
	~Socket();

	bool Run();
	void setConnectParams(const string& _hostname, const string& _port);
	bool Connect();
	void onConnectComplete(bool bConnected);

	bool startTLS();
	bool Write(const string & data);
	void Read(string & readBuffer);
	void Disconnect();
};
