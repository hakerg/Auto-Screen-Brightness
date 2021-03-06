// Launcher.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "stdafx.h"
#include "Launcher.h"
#include <TlHelp32.h>
#include <shellapi.h>


bool IsProcessRunning(const WCHAR * name)
{
	HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (SnapShot == INVALID_HANDLE_VALUE)
		return false;

	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(SnapShot, &procEntry))
		return false;

	do
	{
		if (wcscmp(procEntry.szExeFile, name) == 0)
			return true;
	} while (Process32Next(SnapShot, &procEntry));

	return false;
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_ LPWSTR    lpCmdLine,
					 _In_ int       nCmdShow)
{

	const WCHAR* exeName = L"Auto Brightness Adjuster.exe";

	while (true)
	{
		if (!IsProcessRunning(exeName))
		{
			ShellExecute(NULL, L"open", exeName, NULL, NULL, SW_HIDE);
		}
		Sleep(10000);
	}

}
