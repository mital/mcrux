#include "StdAfx.h"
#include "SocketObj.h"
#include <process.h>
#include <winsock.h>
#include <sys/types.h>

#include "SocketJSObject.h"


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
  port("")
{
	socketObj = socket( AF_INET, SOCK_STREAM, 0 );
	
	InitializeCriticalSection( &m_csReading );
	InitializeCriticalSection( &m_csWriting );
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

unsigned long hostToIP( const string & hostname )
{
	u_long nRemoteAddress = inet_addr( hostname.c_str() );
	if( nRemoteAddress == INADDR_NONE ) {
		hostent* pHE = gethostbyname( hostname.c_str() );
        if( pHE == 0 )
           return INADDR_NONE;
		nRemoteAddress = *((u_long*)pHE->h_addr_list[0]);
	}
	return nRemoteAddress;
}


bool Socket::Connect()
{
	if ((hostname.size() < 0)
		|| (port.size() <= 0))
	{
		return false;
	}

	EnterCriticalSection( &m_csReading );
	EnterCriticalSection( &m_csWriting );

	u_short sPort = ::atoi(port.c_str());
	sockaddr_in sinRemoteServer;
	sinRemoteServer.sin_family = AF_INET;
	sinRemoteServer.sin_addr.s_addr = hostToIP(hostname);
	sinRemoteServer.sin_port = htons(sPort);

	if (connect( socketObj, (sockaddr*)&sinRemoteServer, sizeof(sockaddr_in) ) == SOCKET_ERROR )
	{
		LeaveCriticalSection( &m_csReading );
		LeaveCriticalSection( &m_csWriting );
		//WSAGetLastError();
		return false;
	}

	LeaveCriticalSection( &m_csReading );
	LeaveCriticalSection( &m_csWriting );

	shouldBeRunning = true;
	return true;
}

void Socket::onConnectComplete(bool bConnected)
{
	jsObjectContainer->onConnectComplete(hostname, port, bConnected);
}


bool Socket::Write(const string & data)
{
	EnterCriticalSection( &m_csWriting );

	int writtenByteCount = send(socketObj, (char*) data.c_str(), (int) data.size(), 0 );
	//char buf[10];
	//_itoa_s(writtenByteCount, buf, 10, 10);
	//::MessageBoxA(0, buf, "Bytes written", MB_OK);

	LeaveCriticalSection( &m_csWriting );
	return true;
}


unsigned long Socket::Recv(string & readBuffer)
{
	EnterCriticalSection( &m_csReading );

	char buf[READ_BUFFER_SIZE + 1];
	unsigned long readBytes = recv( socketObj, buf, READ_BUFFER_SIZE, 0);
	//char bufaa[10];
	//_itoa_s(readBytes, bufaa, 10, 10);
	//::MessageBoxA(0, bufaa, "read bytes", MB_OK);
	buf[readBytes] = 0;
	readBuffer += buf;

	LeaveCriticalSection( &m_csReading );
	return readBytes;
}


void Socket::Disconnect()
{
	shouldBeRunning = false;
	shutdown(socketObj, SD_BOTH);
	// store thread id and wait for thread to exit.
}


bool Socket::Run()
{
	string readBuffer;
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 5000;// 5ms

	while(shouldBeRunning)
	{
		readBuffer = "";
		bool read = true;
		bool write = false;
		int selectRet = Select(read, write, &tv);
		if(selectRet == 1)
		{
			Recv(readBuffer);
			jsObjectContainer->handleReadData(readBuffer);
		}
		else if (selectRet == 0)
		{
			// loop again
		}
		else
		{
			shouldBeRunning = false;
		}

	}
	return true;
}

bool Socket::Select(bool read, bool write, timeval * tv)
{
	fd_set fdSet;
	FD_ZERO(&fdSet);
	FD_SET(socketObj, &fdSet);

	return ::select(FD_SETSIZE, read ? &fdSet : NULL, write ? &fdSet : NULL, NULL, tv);
}