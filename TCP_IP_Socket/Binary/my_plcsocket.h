#pragma once
#include <iostream>
//#include <minwindef.h>
#include <WinSock2.h>
#include <atlstr.h>

//#define TARGET_PORT	50001		
#define TARGET_PORT	50000
#define TARGET_PLC	"192.168.0.39"	// юс╫ц

bool SendPLCCommand(CString data, unsigned short *isRet, SOCKET socketStart);
//int PlcSocket(float value,int index, SOCKET socketStart);
int PlcSocket(int addr, unsigned short value, SOCKET socketStart);
bool wordWriteFormat(int iAddr, unsigned short data, SOCKET socketStart);