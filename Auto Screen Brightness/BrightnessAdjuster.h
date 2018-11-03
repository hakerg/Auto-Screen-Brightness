#pragma once

#include <thread>

#include "escapi.h"
#include "gammaramp.h"



class BrightnessAdjuster
{
private:


	std::thread thread;
	bool threadRunning;

	CGammaRamp GammaRamp;
	SimpleCapParams capture;
	bool deviceReady = false;

	static void threadFunc(BrightnessAdjuster* object, DWORD waitMillis, bool deviceAlwaysOn);


public:
	BrightnessAdjuster();
	~BrightnessAdjuster();


	void Adjust(bool leaveDeviceOpen);

	void StartAdjusting(DWORD waitMillis, bool deviceAlwaysOn);
	void StopAdjusting();

	void InitDeviceIfClosed();
	void CloseDeviceIfOpen();
};

