#pragma once

#include <winsock2.h>

#include <iostream>

using namespace std;

class SocketJSObject;
void StartSocketThread(void * socketVoid);

#define KILOBYTE 1024
#define READ_BUFFER_SIZE (128 * KILOBYTE)

class Socket
{
	CRITICAL_SECTION m_csReading;
	CRITICAL_SECTION m_csWriting;

	SocketJSObject* jsObjectContainer;
	bool shouldBeRunning;
	string hostname;
	string port;
	SOCKET  socketObj;

	int Select(bool read, bool write, timeval * tv);

public:

	Socket(SocketJSObject* _jsObjectContainer);
	~Socket();

	bool Run();
	void setConnectParams(const string& _hostname, const string& _port);
	bool Connect();
	void onConnectComplete(bool bConnected);

	bool Write(const string & data);
	unsigned long Recv(string & readBuffer);
	void Disconnect();
};
