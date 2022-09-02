#pragma once


#pragma comment(lib,"C:\\Users\\SNNU-admin\\Desktop\\LogitechG27\\Libraries\\logitech\\Lib\\x64\\LogitechSteeringWheelLib.lib")
#include "C:\Users\SNNU-admin\Desktop\LogitechG27\Libraries\logitech\Include\LogitechSteeringWheelLib.h"



class LogitechWrapper
{
private:
	DIJOYSTATE2* joystick_vars = NULL;

public:
	bool establishConnection();
	DIJOYSTATE2* getWheelVariables();
	void releaseConnection();
};