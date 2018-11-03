// Auto Screen Brightness.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "stdafx.h"
#include "Auto Screen Brightness.h"
#include "BrightnessAdjuster.h"


int WINAPI WinMain(
	HINSTANCE hInstance,      // handle to current instance
	HINSTANCE hPrevInstance,  // handle to previous instance
	LPSTR lpCmdLine,          // command line
	int nCmdShow              // show state
)
{
	//Example for changing the brightness with CGammaRamp class:
	//Be aware that this exmaple may not work properly in all
	//Video cards.

	BrightnessAdjuster brightnessAdjuster;

	while (true)
	{
		brightnessAdjuster.Adjust(false);
		Sleep(60000);
	}


	return 0;
}