#pragma once

#include "escapi.h"
#include "gammaramp.h"



class BrightnessAdjuster
{
private:

	CGammaRamp GammaRamp;
	SimpleCapParams capture;
	bool deviceReady = false;

	double gamma[3] = { -1.0, -1.0, -1.0 };

	void powerShellSetSystemBrightness(int value);


public:
	BrightnessAdjuster();
	~BrightnessAdjuster();


	// brightnessThreshold: <0, 3>
	bool Adjust(int captures, bool leaveDeviceOpen, double brightnessThreshold = 0.0);

	bool TryInitDeviceIfClosed();
	void CloseDeviceIfOpen();
};

