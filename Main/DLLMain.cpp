/*
Copyright 2018 weeab.club

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <strstream>
#include <fstream>
#include <iostream>
#include <ostream>

#include <d3d9.h>

#include "DLLMain.h"
#include "SDK/SDK/Utilities.h"
#include "Injection/ReflectiveLoader.h"
#include "Offsets/Offsets.h"
#include "../Menu/Interface/Interfaces.h"
#include "Hooks/Hooks.h"
#include "SDK/SDK/RenderManager.h"
#include "SDK/SDK/CBulletListener.h"
#include "SDK/SDK/Dumping.h"
#include "../Hacks/Hacks.h"
#include "../Menu/Menu.h"
#include "../Hacks/Features/AntiAim/AntiAntiAim.h"
#include "../Hacks/Misc/HitMarker/hitmarker.h"
#include "AntiLeak/AntiLeak.h"
#include"Windows.h"
#include "Winbase.h"

int missedLogHits[65];
template <int XORSTART, int BUFLEN, int XREFKILLER>

class Xor
{
	private:
		Xor();
	public:
		char s[BUFLEN];

		Xor(const char* xs);
		~Xor()
		{
			for (int i = 0; i < BUFLEN; i++) s[i] = 0;
		}
};

template <int XORSTART, int BUFLEN, int XREFKILLER>

Xor<XORSTART, BUFLEN, XREFKILLER>::Xor(const char* xs)
{
	int xvalue = XORSTART;
	int i = 0;
	for (; i < (BUFLEN - 1); i++)
	{
		s[i] = xs[i - XREFKILLER] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[BUFLEN - 1] = (2 * 2 - 3) - 1;
}

extern HINSTANCE hAppInstance;

UCHAR szFileSys[255], szVolNameBuff[255];
DWORD dwMFL, dwSysFlags;
DWORD dwSerial;
LPCTSTR szHD = "C:\\";

bool ErasePEHeader(HMODULE hModule)
{
	hModule = GetModuleHandle(NULL);
	if ((DWORD)hModule == 0) return 0;
	DWORD IMAGE_NT_HEADER = *(int*)((DWORD)hModule + 60);
	for (int i = 0; i<0x108; i++)
		*(BYTE*)(IMAGE_NT_HEADER + i) = 0;
	for (int i = 0; i<120; i++)
		*(BYTE*)((DWORD)hModule + i) = 0;
	return 1;
}

HINSTANCE HThisModule;
bool DoUnload;


bool is_file_exist(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void create_folder(const char * path) {
	if (!CreateDirectory(path, NULL)) {
		return;
	}
}

void initialize_configs_file() {

	create_folder("weeabcfg");
	create_folder("weeabcfg\\cfg");

	if (!is_file_exist("weeabcfg\\cfg\\weeabcfg_configs.txt")) {
		std::ofstream("weeabcfg\\cfg\\weeabcfg_configs.txt");
	}
}

void CAntiLeak::ErasePE()
{
	char *pBaseAddr = (char*)GetModuleHandle(NULL);
	DWORD dwOldProtect = 0;
	VirtualProtect(pBaseAddr, 4096, PAGE_READWRITE, &dwOldProtect);
	ZeroMemory(pBaseAddr, 4096);
	VirtualProtect(pBaseAddr, 4096, dwOldProtect, &dwOldProtect);
}

int InitialThread()
{
	PrintMetaHeader();
	initialize_configs_file();
	Offsets::Initialise();
	Interfaces::Initialise();
	NetVar.RetrieveClasses();
	NetvarManager::Instance()->CreateDatabase();
	Render::Initialise();
	hitmarker::singleton()->initialize();
	Hacks::SetupHacks();
	Options::SetupMenu();
	Hooks::Initialise();
	CBulletListener::singleton()->init();
	FLASHWINFO flash;
	flash.cbSize = sizeof(FLASHWINFO);
	flash.hwnd = Interfaces::window;
	flash.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
	flash.uCount = 0;
	flash.dwTimeout = 0;
	FlashWindowEx(&flash);
	while (DoUnload == false)
	{
		Sleep(1000);
	}
	Hooks::UndoHooks();
	Sleep(2000);
	FreeLibraryAndExitThread(HThisModule, 0);
	return 0;
}



BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	GetVolumeInformation(szHD, (LPTSTR)szVolNameBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		GetVolumeInformation(szHD, (LPTSTR)szVolNameBuff, 255, &dwSerial, &dwMFL, &dwSysFlags, (LPTSTR)szFileSys, 255);
		Sleep(100);
		{
			{
				DisableThreadLibraryCalls(hModule);

				CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)InitialThread, NULL, NULL, NULL);

				return TRUE;
			}
		}
		return FALSE;
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		VOID WINAPI FreeLibraryAndExitThread(
			_In_ HMODULE hModule,
			_In_ DWORD   dwExitCode
		);
	{
	}
	return TRUE;
}