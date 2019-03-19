#pragma once
#include "NetPackage.h"

struct ReceiveResult
{
	unsigned int m_fromAddress = NULL;
	unsigned int m_fromPort = NULL;

	ReceiveResult()
	{
	}
	ReceiveResult(unsigned int fromAdress, unsigned int fromPort)
	{
		m_fromAddress = fromAdress;
		m_fromPort = fromPort;
	}

	unsigned int GetAdress()
	{
		return m_fromAddress;
	}
	unsigned int GetPort()
	{
		return m_fromPort;
	}

};

class NetSocketUDP
{
private:
	int m_handle = 0;
public:

	NetSocketUDP();
	NetSocketUDP(const NetSocketUDP&);
	~NetSocketUDP();

	NetResult OpenSocket(short port);
	NetResult CloseSocket();
	
	NetResult Send(NetPackage& netPackage);
	ReceiveResult Receive(unsigned char* dataArray, unsigned int dataArrayLength);

	NetResult EnableNonBlocking();
	NetResult DisableNonBlocking();
	bool IsOpen() const;
};