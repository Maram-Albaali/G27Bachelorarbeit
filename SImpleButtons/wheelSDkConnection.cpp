#include "stdafx.h"
#include <iostream>

// Direct Input
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <dinput.h>

// Logitech Wheel SDK
#pragma comment(lib, "LogitechSteeringWheelLib.lib")
#include "LogitechSteeringWheelLib.h"

LPDIRECTINPUT8 di;
HRESULT hr;
LPDIRECTINPUTDEVICE8 wheel;

BOOL CALLBACK EnumCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{
	HRESULT hr;

	bool result = LogiSteeringInitialize(false);
	std::cout << result;


	// Obtain an interface to the enumerated wheel.
	//hr = di->CreateDevice(instance->guidInstance, &wheel, NULL);

	// If it failed, then we can't use this wheel. (Maybe the user unplugged
	// it while we were in the middle of enumerating it.)
	if (FAILED(result)) {
		return DIENUM_CONTINUE;
	}

	// Stop enumeration. Note: we're just taking the first wheel we get. You
	// could store all the enumerated wheels and let the user pick.
	return DIENUM_STOP;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Create a DirectInput device
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&di, NULL))) {
		return hr;
	}

	// Look for the first wheel we can find.
	if (FAILED(hr = di->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumCallback,
		NULL, DIEDFL_ATTACHEDONLY))) {
		return hr;
	}

	// Make sure we got a wheel
	if (wheel == NULL) {
		printf("Wheel not found.\n");
		return E_FAIL;
	}

	// SDK Snippets
	{
		// Sample implementation of LogiSetOperatingRangeDInput only using part of the SDK.
		int range = 900;
		if (LogiSetOperatingRangeDInput(wheel, range))
		{
			printf("LogiSetOperatingRangeDInput with range = %d was successful.\n", range);
		}
		else
		{
			printf("LogiSetOperatingRangeDInput with range = %d failed.\n", range);
		}

		// Sample implementation of LogiGetOperatingRangeDInput only using part of the SDK.
		int newRange = 0;
		if (LogiGetOperatingRangeDInput(wheel, newRange))
		{
			printf("LogiSetOperatingRangeDInput returned newRange = %d.\n", newRange);
		}
		else
		{
			printf("LogiSetOperatingRangeDInput failed.\n");
		}



		system("pause");
		return 0;
	}