#include "stdafx.h"
#include "ColorModeSwitcher.h"
#include <ctime>
#include <string>


ColorModeSwitcher::ColorModeSwitcher()
{
}


ColorModeSwitcher::~ColorModeSwitcher()
{
}

bool ColorModeSwitcher::IsDay()
{

	time_t nullTime = time(nullptr);
	tm currentTime;
	localtime_s(&currentTime, &nullTime);

	return currentTime.tm_hour >= 6 && currentTime.tm_hour < 18;

}

void ColorModeSwitcher::SwitchMode(bool day, bool colorPrevalence)
{

	std::string data(day ? "1" : "0");

	system(("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v SystemUsesLightTheme /t REG_DWORD /d " + data + " /f").c_str());
	system(("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v AppsUseLightTheme /t REG_DWORD /d " + data + " /f").c_str());

	if (day) SetColorPrevalence(false);
	else SetColorPrevalence(colorPrevalence);
}

void ColorModeSwitcher::SetColorPrevalence(bool prevalence)
{
	std::string data(prevalence ? "1" : "0");

	system(("REG ADD HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize /v ColorPrevalence /t REG_DWORD /d " + data + " /f").c_str());
}

void ColorModeSwitcher::SwitchMode(bool colorPrevalence)
{
	SwitchMode(IsDay(), colorPrevalence);
}
