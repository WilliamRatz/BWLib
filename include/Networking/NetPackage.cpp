#include "NetPackage.h"


NetPackage::NetPackage(NetAddress* p_netAdress, unsigned char* p_dataArray, unsigned int p_dataSize)
{
	m_adress = p_netAdress;
	m_dataArray = p_dataArray;
	m_dataSize = p_dataSize;
}

NetPackage::NetPackage(const NetPackage& p_netPackage)
{
	m_adress = p_netPackage.m_adress;
	m_dataArray = p_netPackage.m_dataArray;
	m_dataSize = p_netPackage.m_dataSize;
}

NetPackage::~NetPackage()
{
}

NetAddress* NetPackage::GetNetAddressRef()
{
	return m_adress;
}

unsigned char* NetPackage::GetDataArrayPtr()
{
	return m_dataArray;
}

unsigned int& NetPackage::GetDataSizeRef()
{
	return m_dataSize;
}
