#include "NetAddress.h"
#include "NetDefine.h"

NetAddress::NetAddress(unsigned char p_ip_A, unsigned char p_ip_B, unsigned char p_ip_C, unsigned char p_ip_D, unsigned short p_port)
{
	m_port = p_port;
	m_address = (p_ip_A << 24) | (p_ip_B << 16) | (p_ip_C << 8) | p_ip_D;

	
}
NetAddress::NetAddress(const NetAddress& p_NetAddress)
{
	m_port = p_NetAddress.m_port;
	m_address = p_NetAddress.m_address;
}


NetAddress::~NetAddress()
{
}

unsigned int& NetAddress::GetAddressRef()
{
	return m_address;
}

unsigned short& NetAddress::GetPortRef()
{
	return m_port;
}
