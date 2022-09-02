// SteeringWheelSDKDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#include "resource.h"		// main symbols

#define CALIBRATE_MSG WM_APP

enum CALIBRATE_CONTROL {
	SKIP = -1,
	SAVE = -2,
	CANCEL = -3,

	WHEEL = 0,
	ACCELERATOR = 1,
	BRAKE = 2,
	CLUTCH = 3,

	X_AXIS = 1,
	Y_AXIS = 2,
	Z_AXIS = 3,
	SLIDER_0 = 4,
	SLIDER_1 = 5,
	X_ROT = 6,
	Y_ROT = 7,
	Z_ROT = 8,
};

