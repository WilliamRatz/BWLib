#pragma once
#include "NetAddress.h"

class NetPackage
{
private:
	NetAddress*		m_adress;
	unsigned char*	m_dataArray;
	unsigned int	m_dataSize;

public:
	NetPackage		(NetAddress* netAdress, unsigned char* dataArray, unsigned int dataSize);
	NetPackage		(const NetPackage&);
	~NetPackage		();

	NetAddress*		GetNetAddressRef();
	unsigned char*	GetDataArrayPtr();
	unsigned int&	GetDataSizeRef();
};

