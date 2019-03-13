#include "Inc_BWNetworking.h"
#include "Inc_SmartMacros.h"
#include "Inc_BWMath.h"
#include <bitset>
using namespace std;

void callbackfunc(unsigned char* dataArray, unsigned int arraySize)
{
	Print(dataArray[0]);
	Print(dataArray[1]);
	Print(dataArray[2]);
	Print(dataArray[3]);
	Print(dataArray[4]);
	Print(dataArray[5]);
	Print(dataArray[6]);
}

void main()
{
	NetSocketUDP udpSocket;
	NetAddress	adress(127, 0, 0, 1, 4000);

	unsigned char sendArray[]{'a', 'b', 'r', 'd', 'e', 'f', 'g', 'h', 'i'};
	NetPackage	package(&adress, sendArray, sizeof(sendArray));


	Println(BWNet::InitializeSocketLayer().m_errorCode);
	Println(udpSocket.OpenSocket(4000).m_errorCode);
	Println(udpSocket.Send(package).m_errorCode);

	while (true)
	{

	udpSocket.Receive(adress, callbackfunc, 500);
	}

	int b = NULL;
	if (!b) 
	{
	Println("drf" );

	}

	std::cin >> b;
}