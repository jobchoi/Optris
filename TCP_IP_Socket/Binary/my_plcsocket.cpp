#pragma once

#pragma comment(lib, "ws2_32.lib")

#include "my_plcsocket.h"

//int PlcSocket(float value, int index, SOCKET socketStart)
int PlcSocket(int addr, unsigned short value, SOCKET socketStart)
{
	//	unsigned short u_value = (unsigned short)*value;
	try {
//		if (wordWriteFormat(1060 + index, *value, socketStart) == false)		// 1060¹øÁö write | origin
		if (wordWriteFormat(addr, value, socketStart) == false)					// 1060 -> 1090
		{//			perror("wordWrite return false");	

			return -4;
		}
	}

	catch (const std::invalid_argument &ex)
	{
		//		std::cerr << "Invalid argument while converting string to number" << std::endl;
		//		std::cerr << "Error" << ex.what() << std::endl;
		ex.what();
		return -5;	//holding
	}
	catch (const std::out_of_range &ex)
	{
		//		std::cerr << "Invalid argument while converting string to number" << std::endl;
		//std::cerr << "Error" << ex.what() << std::endl;
		ex.what();
		return -5; //holding
	}

	
}

bool wordWriteFormat(int iAddr, unsigned short data, SOCKET socketStart)
{
	bool bRet;
	int iAddr_index;
	unsigned short usReturn = 0;
	CString sendData;

	std::cout << "=============================================================================================================" << std::endl;

	sendData.Format(_T("500000FF03FF00001C001014010000D*%06d0001%04X"), iAddr , data);
	bRet = SendPLCCommand(sendData, &usReturn, socketStart);		
	std::cout << "bRet : " << bRet << std::endl;
	std::cout << "=============================================================================================================" << std::endl;

	return bRet;
}


bool SendPLCCommand(CString sendData, unsigned short* isRet, SOCKET socketStart)
{
	int length = sendData.GetLength(), index = 0;
	CStringA ansiString(sendData);

	if (send(socketStart, ansiString, sendData.GetLength(), 0) < 0)
		return false;
	else
		return true;
}