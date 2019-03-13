#include "Inc_BWNetworking.h"
#include "Inc_SmartMacros.h"
#include "Inc_BWMath.h"
#include <bitset>
using namespace std;

void main()
{

	NetSocketUDP udpSocket;
	NetAddress	adress(127, 0, 0, 1, 4000);

	unsigned char sendArray[]{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
	NetPackage	package(&adress, sendArray, sizeof(sendArray));


	Println(BWNet::InitializeSocketLayer().m_errorCode);
	Println(udpSocket.OpenSocket(4000).m_errorCode);
	Println(udpSocket.Send(package).m_errorCode);




	int a = NULL;
	if (!a) 
	{
	Println("drf" );

	}
	std::cin >> a;
}