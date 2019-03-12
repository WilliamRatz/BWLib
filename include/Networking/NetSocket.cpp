#include "NetSocket.h"


NetSocket::NetSocket(short p_Port)
{
}


NetSocket::~NetSocket()
{
}

void NetSocket::ShutdownSockets()
{
	#if PLATFORM == PLATFORM_WINDOWS
		WSACleanup();
	#endif
}
