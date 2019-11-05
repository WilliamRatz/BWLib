#include "NetSocketTCP.h"

NetSocketTCP::NetSocketTCP()
{
}

NetSocketTCP::NetSocketTCP(const NetSocketTCP& p_NetSocketTCP)
{
	m_handle = p_NetSocketTCP.m_handle;
}

NetSocketTCP::~NetSocketTCP()
{
}

int NetSocketTCP::GetDesciptor()
{
	return m_handle;
}

NetResult NetSocketTCP::OpenSocket(unsigned short p_port)
{
	m_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_handle == INVALID_SOCKET)
	{
		return NetResult(2);
	}


	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.S_un.S_addr = INADDR_ANY;
	address.sin_port = htons(p_port);

	if (bind(m_handle, (const sockaddr*)&address, sizeof(address)) < 0)
	{
		return NetResult(3);
	}

	return NetResult(0);
}

NetResult NetSocketTCP::CloseSocket()
{
#if PLATFORM == BWLIB_PLATFORM_MAC || PLATFORM == BWLIB_PLATFORM_UNIX
	if (close(m_handle) != 0)
	{
		return NetResult(7);
	}
#elif PLATFORM == BWLIB_PLATFORM_WINDOWS
	if (closesocket(m_handle) != 0)
	{
		return NetResult(7);
	}
#endif
	return NetResult(0);
}

NetResult NetSocketTCP::Send(char* dataArray, int dataArrayLength)
{
	if (send(m_handle, dataArray, dataArrayLength, 0) == SOCKET_ERROR)
	{
		return NetResult(11);
	}
	return NetResult(0);
}

NetResult NetSocketTCP::Receive(char* dataArray, int dataArrayLength, int& receivedBytesLength)
{
	receivedBytesLength = recv(m_handle, dataArray, dataArrayLength, 0);
	if (receivedBytesLength == SOCKET_ERROR)
	{
		return NetResult(12);
	}
	return NetResult(0);
}

NetResult NetSocketTCP::SetListeningMode()
{
	if (listen(m_handle, SOMAXCONN))
	{
		return NetResult(10);
	}
	return NetResult(0);
}

NetResult NetSocketTCP::EnableTCP_NODELAY()
{
	int yes = 1;
	setsockopt(m_handle, IPPROTO_TCP, TCP_NODELAY, (char*)&yes, sizeof(int));    // 1 - on, 0 - off

	return NetResult(0);
}

NetResult NetSocketTCP::DisableTCP_NODELAY()
{
	int no = 0;
	setsockopt(m_handle, IPPROTO_TCP, TCP_NODELAY, (char*)&no, sizeof(int));    // 1 - on, 0 - off

	return NetResult(0);
}

NetResult NetSocketTCP::AcceptConnection(NetSocketTCP& newSocket, NetAddress& connectedAddress)
{
	int tempSize = sizeof(sockaddr_in);
	newSocket.m_handle = accept(m_handle, (sockaddr*)&connectedAddress.GetTransportAddress(), &tempSize);
	if (newSocket.m_handle == INVALID_SOCKET)
	{
		return NetResult(9);
	}
	return NetResult(0);
}

NetResult NetSocketTCP::AcceptConnection(NetSocketTCP& newSocket)
{
	int tempSize = sizeof(sockaddr_in);
	newSocket.m_handle =  accept(m_handle, NULL, NULL);
	if (newSocket.m_handle == INVALID_SOCKET)
	{
		return NetResult(9);
	}
	return NetResult(0);
}

NetResult NetSocketTCP::ConnectTo(NetAddress listeningAddress)
{
	if (connect(m_handle, (sockaddr*)&listeningAddress.GetTransportAddress(), sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		return NetResult(8);
	}

	return NetResult(0);
}

bool NetSocketTCP::IsOpen() const
{
	if (m_handle == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}
