
#include "my_plcsocket.h"

#include<stdlib.h>
#include<time.h>

SOCKET startsocket;

// ================================= 함수 선언
int my_socketstart_function();

void srand(unsigned int seed);

int main(int argc, char* argv[]) {
	SOCKET startsocket_test;
	int i = 0, addr = 1060;
	int cnt = 20;
	unsigned short testdata[2] = { };
//	unsigned short testdata1 = ;
	std::cout << "start socket" << std::endl;
	std::cout << "return : " << my_socketstart_function() << std::endl;

	std::cout << "start tx data" << std::endl;
	srand(time(NULL));
	startsocket_test = startsocket;
	do
	{
		if (i >= 2) 
			i= 0;
		
		if (addr > 1061)
			addr = 1060;
			
		testdata[i] = rand() % 100;
			
		if (PlcSocket(addr, testdata[i], startsocket_test) == true) {				
			i++; addr++;
			continue;
		} 
					
	
	} while (cnt--);

	WSACleanup();
	closesocket(startsocket_test);

	return 0;
}



// ======================================= 함수 정의 =======================================
int my_socketstart_function()
{
	WORD wVersionRequested;
	SOCKET my_socketStart;
	SOCKADDR_IN target;
	WSADATA wsData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsData);

	if (err != 0)
	{
		//		std::cout << "WSAStartup error %ld" << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

	// address famliy Internet
	target.sin_family = AF_INET;
	//	Targer port
	target.sin_port = htons(TARGET_PORT);
	//	Target IP
	target.sin_addr.s_addr = inet_addr(TARGET_PLC);

	// ======================================== SOCKET 분리중 ========================================
	my_socketStart = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (my_socketStart == INVALID_SOCKET)
	{
		//	std::cout << "socket() error : " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -2;
	}

	if (connect(my_socketStart, reinterpret_cast<SOCKADDR*>(&target), sizeof(target)) == SOCKET_ERROR)
	{//		std::cout << "Plz start on server" << std::endl;
		WSACleanup();
		return -3;
	}

	startsocket = my_socketStart;
	// ======================================== SOCKET 분리중 ========================================
}