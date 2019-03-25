#pragma once
#include "NetAddress.h"

/*
TCP establishes a connction between two PC's 
and the socket can only send to the connected 
PC and no one else
*/
class NetSocketTCP
{
private:

public:
	SOCKET m_handle = -1;
	NetSocketTCP();
	NetSocketTCP(const NetSocketTCP&);
	~NetSocketTCP();

	NetResult OpenSocket(unsigned short port);
	NetResult CloseSocket();

	NetResult Send(char* dataArray, int dataArrayLength);
	NetResult Receive(char* dataArray, int dataArrayLength);

	//To disable the ListeningMode you have to close the socket
	NetResult SetListeningMode();

	/*
		normally used in in loop continusly to accept if someone asked for connection
		if a acceptConnection happens a new socket will be created wich can send an receive 
	*/
	NetResult AcceptConnection(NetSocketTCP& newSocket, NetAddress& connectedAddress);
	NetResult AcceptConnection(NetSocketTCP& newSocket);
	
	/*
		connecting to a TCP Port wich is in listening mode
		(Warning: You don't connect to the actul port for what you asking)
	*/
	NetResult ConnectTo(NetAddress listeningAddress);

	//Check if this port is allready opened 
	bool IsOpen() const;
};

