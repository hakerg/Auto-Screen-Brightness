#include "stdafx.h"
#include "BrightnessAdjuster.h"


void BrightnessAdjuster::Adjust(int captures, bool leaveDeviceOpen)
{

	InitDeviceIfClosed();


	for (int n = 0; n < captures; n++)
	{
		/* request a capture */
		doCapture(0);

		while (isCaptureDone(0) == 0)
		{
			Sleep(1);
			/* Wait until capture is done. */
		}

	}
	
	
	double avgR = 0, avgG = 0, avgB = 0;

	int iMax = 320 * 240;
	for (int i = 0; i < iMax; i++)
	{

		BYTE* pixel = (BYTE*)(capture.mTargetBuf + i);

		avgB += pixel[0];
		avgG += pixel[1];
		avgR += pixel[2];

	}

	avgR /= iMax;
	avgG /= iMax;
	avgB /= iMax;

	/*if (avgR == 0 && avgG == 0 && avgB == 0)
	{
		Adjust(leaveDeviceOpen);
	}
	else
	{*/

		GammaRamp.SetBrightness(NULL, (WORD)avgR, (WORD)avgG, (WORD)avgB);


		if (!leaveDeviceOpen)
		{
			CloseDeviceIfOpen();
		}
	//}



}

void BrightnessAdjuster::InitDeviceIfClosed()
{

	if (!deviceReady)
	{

		if (initCapture(0, &capture) == 0)
		{
			printf("Capture failed - device may already be in use.\n");
			return;
		}
		else
		{
			deviceReady = true;
		}

	}


}

void BrightnessAdjuster::CloseDeviceIfOpen()
{

	if (deviceReady)
	{
		deinitCapture(0);
		deviceReady = false;
	}

}

void BrightnessAdjuster::threadFunc(BrightnessAdjuster * object, DWORD waitMillis, int captures, bool deviceAlwaysOn)
{

	while (object->threadRunning)
	{

		object->Adjust(captures, deviceAlwaysOn);
		Sleep(waitMillis);

	}

}

BrightnessAdjuster::BrightnessAdjuster()
{

	int devices = setupESCAPI();

	if (devices == 0)
	{
		printf("ESCAPI initialization failure or no devices found.\n");
		return;
	}

	capture.mWidth = 320;
	capture.mHeight = 240;
	capture.mTargetBuf = new int[320 * 240];

}


BrightnessAdjuster::~BrightnessAdjuster()
{

	CloseDeviceIfOpen();
	GammaRamp.ResetBrightness(NULL);

	delete[] capture.mTargetBuf;

}

void BrightnessAdjuster::StartAdjusting(DWORD waitMillis, int captures, bool deviceAlwaysOn)
{

	threadRunning = true;
	thread = std::thread(threadFunc, this, waitMillis, captures, deviceAlwaysOn);

}

void BrightnessAdjuster::StopAdjusting()
{

	threadRunning = false;
	thread.join();

}
