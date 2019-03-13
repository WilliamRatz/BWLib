#pragma once
#include <string>
#include "NetDefine.h"

class BWNet
{
public:
	BWNet();
	~BWNet();

	static NetResult InitializeSocketLayer();
	static void ShutdownSockets();
	
	std::string ErrorDecoder(short errorCode);

};


