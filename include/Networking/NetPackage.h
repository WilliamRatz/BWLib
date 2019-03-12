#pragma once

class NetPackage
{
private:
	short socketPort;
	unsigned int adress;
	unsigned char data[];

public:
	NetPackage();
	~NetPackage();
};

