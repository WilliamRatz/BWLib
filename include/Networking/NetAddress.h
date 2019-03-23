#pragma once

#include "NetDefine.h"
class NetAddress
{
private:
	sockaddr_in m_addr;

public:
	NetAddress();
	NetAddress(	unsigned char ip_A,
				unsigned char ip_B,
				unsigned char ip_C,
				unsigned char ip_D,
				unsigned short port);

	NetAddress(unsigned int ipv4, unsigned short port);

	NetAddress			(const NetAddress&);
	~NetAddress			();

	sockaddr_in&			GetTransportAddress();
	const unsigned int		GetIpv4Ref();
	const unsigned short	GetPortRef();
};

