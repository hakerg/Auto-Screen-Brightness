// Auto Screen Brightness.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "stdafx.h"
#include "Auto Screen Brightness.h"
#include "BrightnessAdjuster.h"
#include <string>
#include <Windows.h>


int main()
{
	//Example for changing the brightness with CGammaRamp class:
	//Be aware that this exmaple may not work properly in all
	//Video cards.

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	BrightnessAdjuster brightnessAdjuster;


	while (true)
	{
		brightnessAdjuster.Adjust(2, true, 0.125);
		Sleep(1000);
	}


	return 0;
}