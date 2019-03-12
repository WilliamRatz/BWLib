#pragma once
#include <string>

class BWNet
{
public:
	BWNet();
	~BWNet();


	static void ShutdownSockets();

	static NetResult SendPackage();

	std::string ErrorDecoder(short errorCode);

};

struct NetResult
{
	bool authorized = true;
	short errorCode = 0;
};

