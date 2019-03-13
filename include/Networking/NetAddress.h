#pragma once

class NetAddress
{
private:
	unsigned int	m_address = 0;
	unsigned short	m_port;

public:
	NetAddress(	unsigned char ip_A,
				unsigned char ip_B,
				unsigned char ip_C,
				unsigned char ip_D,
				unsigned short port);

	NetAddress			(const NetAddress&);
	~NetAddress			();

	unsigned int&		GetAddressRef();
	unsigned short&		GetPortRef();
};

