#pragma once
#include "NetAddress.h"

class NetSocketUDP
{
private:
	SOCKET m_handle = 0;
public:

	NetSocketUDP();
	NetSocketUDP(const NetSocketUDP&);
	~NetSocketUDP();

	NetResult OpenSocket(unsigned short port);
	NetResult CloseSocket();
	
	NetResult Send(NetAddress netAddress, char* dataArray, unsigned int dataArrayLength);
	NetAddress Receive(char* dataArray, unsigned int dataArrayLength);

	NetResult EnableNonBlocking();
	NetResult DisableNonBlocking();
	bool IsOpen() const;
};