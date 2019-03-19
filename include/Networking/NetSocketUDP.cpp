#include "NetDefine.h"
#include "NetSocketUDP.h"

#include "../Inc_SmartMacros.h"


NetSocketUDP::NetSocketUDP()
{


}
NetSocketUDP::NetSocketUDP(const NetSocketUDP& p_NetSocketUDP)
{
	m_handle = p_NetSocketUDP.m_handle;
}
NetSocketUDP::~NetSocketUDP()
{
}

NetResult NetSocketUDP::OpenSocket(short p_port)
{
	m_handle = static_cast<int>(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));

	if (m_handle <= 0)
	{
		return NetResult(false, 2);
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons((unsigned short)p_port);

	if (bind(m_handle, (const sockaddr*)&address, sizeof(sockaddr_in)) < 0)
	{
		return NetResult(false, 3);
	}

	return NetResult(true, 0);
}
NetResult NetSocketUDP::CloseSocket()
{
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	if (close(m_handle) != 0)
	{
		return NetResult(false, 7);
	}
#elif PLATFORM == PLATFORM_WINDOWS
	if (closesocket(m_handle) != 0)
	{
		return NetResult(false, 7);
	}
#endif
	return NetResult(true, 0);
}

NetResult NetSocketUDP::Send(NetPackage& p_netPackage)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(p_netPackage.GetNetAddressRef()->GetAddressRef());
	addr.sin_port = htons(p_netPackage.GetNetAddressRef()->GetPortRef());

	int sent_bytes = sendto(m_handle, (const char*)p_netPackage.GetDataArrayPtr(), p_netPackage.GetDataSizeRef(), 0, (sockaddr*)&addr, sizeof(sockaddr_in));

	if (sent_bytes != p_netPackage.GetDataSizeRef())
	{
		return NetResult(false, 6);
	}

	return NetResult(true, 0);
}
ReceiveResult NetSocketUDP::Receive(unsigned char* p_dataArray, unsigned int p_dataArrayLength)
{
#if PLATFORM == PLATFORM_WINDOWS
	typedef int socklen_t;
#endif

	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int bytes = recvfrom(m_handle,
		(char *)p_dataArray,
		p_dataArrayLength,
		0,
		(sockaddr*)&from,
		&fromLength);

	if (bytes <= 0)
		return ReceiveResult();

	return ReceiveResult(ntohl(from.sin_addr.s_addr), ntohs(from.sin_port));
}

NetResult NetSocketUDP::EnableNonBlocking()
{
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	int nonBlocking = 1;
	if (fcntl(m_handle,
		F_SETFL,
		O_NONBLOCK,
		nonBlocking) == -1)
	{
		return NetResult(false, 4);
	}

#elif PLATFORM == PLATFORM_WINDOWS

	DWORD nonBlocking = 1;
	if (ioctlsocket(m_handle,
		FIONBIO,
		&nonBlocking) != 0)
	{
		return NetResult(false, 4);
	}

#endif
	return NetResult(true, 0);
}
NetResult NetSocketUDP::DisableNonBlocking()
{
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
	int nonBlocking = 0;
	if (fcntl(m_handle,
		F_SETFL,
		O_NONBLOCK,
		nonBlocking) == -1)
	{
		return NetResult(false, 5);
	}

#elif PLATFORM == PLATFORM_WINDOWS

	DWORD nonBlocking = 0;
	if (ioctlsocket(m_handle,
		FIONBIO,
		&nonBlocking) != 0)
	{
		return NetResult(false, 5);
	}

#endif

	return NetResult(true, 0);
}
bool NetSocketUDP::IsOpen() const
{
	if (m_handle <= 0)
	{
		return false;
	}
	return true;
}