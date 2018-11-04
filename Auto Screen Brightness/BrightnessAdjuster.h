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

	static void threadFunc(BrightnessAdjuster* object, DWORD waitMillis, int captures, bool deviceAlwaysOn);


public:
	BrightnessAdjuster();
	~BrightnessAdjuster();


	void Adjust(int captures, bool leaveDeviceOpen);

	void StartAdjusting(DWORD waitMillis, int captures, bool deviceAlwaysOn);
	void StopAdjusting();

	void InitDeviceIfClosed();
	void CloseDeviceIfOpen();
};

