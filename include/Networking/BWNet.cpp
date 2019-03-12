// platform detection
#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define PLATFORM PLATFORM_MAC
#else
#define PLATFORM PLATFORM_UNIX
#endif
#if PLATFORM == PLATFORM_WINDOWS

#include <winsock2.h>
#pragma comment( lib, "wsock32.lib" )

#elif PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#endif

#include "BWNet.h"

BWNet::BWNet()
{
}


BWNet::~BWNet()
{
}

void BWNet::ShutdownSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSACleanup();
#endif
}

NetResult BWNet::SendPackage()
{}

std::string BWNet::ErrorDecoder(short errorCode)
{
	switch (errorCode)
	{
		case 0:
			return "No Error occurred"; 
			break;
		case 1:
			return "Failed to send packet";
			break;
		
		
		default:
			return "Error code unknown";
			break;

	}
	return std::string();
}
