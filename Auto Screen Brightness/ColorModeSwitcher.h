#pragma once
class ColorModeSwitcher
{
public:
	ColorModeSwitcher();
	~ColorModeSwitcher();


	static bool IsDay();

	static void SwitchMode(bool day, bool colorPrevalence);

	static void SetColorPrevalence(bool prevalence);


	static void SwitchMode(bool colorPrevalence);

};

