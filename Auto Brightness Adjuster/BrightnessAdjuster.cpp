#include "stdafx.h"
#include "BrightnessAdjuster.h"
#include <string>
#include <Windows.h>


bool BrightnessAdjuster::Adjust(int captures, bool leaveDeviceOpen, double brightnessThreshold)
{

	if (!TryInitDeviceIfClosed()) return false;


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


	if (!leaveDeviceOpen)
	{
		CloseDeviceIfOpen();
	}
	
	
	double newGamma[3] = { 0, 0, 0 };

	int pixelCount = 320 * 240;
	for (int i = 0; i < pixelCount; i++)
	{

		BYTE* pixel = (BYTE*)(capture.mTargetBuf + i);

		for (int n = 0; n < 3; n++)
		{
			newGamma[n] += pixel[2 - n];
		}

	}
	for (int n = 0; n < 3; n++)
	{
		newGamma[n] /= pixelCount * 255;
	}


	double newBrightness = newGamma[0];
	if (newGamma[1] > newBrightness) newBrightness = newGamma[1];
	if (newGamma[2] > newBrightness) newBrightness = newGamma[2];

	newBrightness = min(newBrightness * 1.5, 1.0);


	if (abs(newGamma[0] - gamma[0]) + abs(newGamma[1] - gamma[1]) + abs(newGamma[2] - gamma[2]) >= brightnessThreshold)
	{

		powerShellSetSystemBrightness(int(newBrightness * 100.0));


		for (int n = 0; n < 3; n++)
		{
			gamma[n] = newGamma[n];
			if (newGamma[n] > 0.5) newGamma[n] = 0.5;
		}

		GammaRamp.SetBrightness(NULL, (WORD)(newGamma[0] * 255), (WORD)(newGamma[1] * 255), (WORD)(newGamma[2] * 255));
		//std::cout << gamma[0] << ", " << gamma[1] << ", " << gamma[2] << std::endl;

		return true;

	}

	return false;
}

bool BrightnessAdjuster::TryInitDeviceIfClosed()
{

	if (getCaptureErrorCode(0))
	{
		CloseDeviceIfOpen();
	}

	if (!deviceReady)
	{

		if (initCapture(0, &capture) == 0)
		{
			printf("Capture failed - device may already be in use.\n");
		}
		else
		{
			deviceReady = true;
		}

	}

	return deviceReady;

}

void BrightnessAdjuster::CloseDeviceIfOpen()
{

	if (deviceReady)
	{
		deinitCapture(0);
		deviceReady = false;
	}

}

void BrightnessAdjuster::powerShellSetSystemBrightness(int value)
{
	std::string command = "PowerShell -Command (Get-WmiObject -Namespace root\\wmi -Class WmiMonitorBrightnessMethods).wmisetbrightness(5, " + std::to_string(value) + ")";

	//system(command.c_str());
	WinExec(command.c_str(), SW_HIDE);
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
