#include "NetAddress.h"

NetAddress::NetAddress()
{
}

NetAddress::NetAddress(unsigned char p_ip_A, unsigned char p_ip_B, unsigned char p_ip_C, unsigned char p_ip_D, unsigned short p_port)
{
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = htonl(((p_ip_A << 24) | (p_ip_B << 16) | (p_ip_C << 8) | p_ip_D));
	m_addr.sin_port = htons(p_port);
}
NetAddress::NetAddress(unsigned int p_ipv4, unsigned short p_port)
{
	m_addr.sin_addr.s_addr = htonl(p_ipv4);
	m_addr.sin_port = htons(p_port);
}
NetAddress::NetAddress(const NetAddress& p_NetAddress)
{
	m_addr = p_NetAddress.m_addr;
}


NetAddress::~NetAddress()
{
}

sockaddr_in& NetAddress::GetTransportAddress()
{
	return m_addr;
}

const unsigned int NetAddress::GetIpv4Ref()
{
	return ntohl(m_addr.sin_addr.s_addr);
}

const unsigned short NetAddress::GetPortRef()
{
	return ntohs(m_addr.sin_port);
}
