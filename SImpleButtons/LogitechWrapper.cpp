#include "LogitechWrapper.h"

bool LogitechWrapper::establishConnection()
{
	bool result = LogiSteeringInitialize(true);

	joystick_vars = new DIJOYSTATE2();
	if (joystick_vars == NULL || result == FALSE)
		return(false);
	return(true);
}  
 
DIJOYSTATE2* LogitechWrapper::getWheelVariables()
{	
	joystick_vars = LogiGetState(0);
	return(joystick_vars);
}
