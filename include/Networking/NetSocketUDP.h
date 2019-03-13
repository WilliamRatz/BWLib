#pragma once
#include "NetPackage.h"

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
	void Receive(NetAddress& receiveAdress, void callbackData(unsigned char* dataArray, unsigned int arraySize), unsigned int maxReceiveSize);

	NetResult EnableNonBlocking();
	NetResult DisableNonBlocking();
	bool IsOpen() const;


};

