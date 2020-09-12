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
#pragma once

#include "../../../Includes/CommonIncludes.h"
#include <time.h>

#define FOREGROUND_WHITE		    (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW       	(FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_CYAN		        (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_MAGENTA	        (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_BLACK		    0

#define FOREGROUND_INTENSE_RED		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_GREEN	(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_BLUE		(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_WHITE	(FOREGROUND_WHITE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_YELLOW	(FOREGROUND_YELLOW | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_CYAN		(FOREGROUND_CYAN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA	(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)

namespace Utilities
{
	void OpenConsole(std::string Title);
	void CloseConsole();
	void Log(const char *fmt, ...);

	void EnableLogFile(std::string filename);

	void SetConsoleColor(WORD color);  

	std::string GetTimeString();
	
	namespace Memory
	{

		DWORD WaitOnModuleHandle(std::string moduleName);

		DWORD FindPattern(std::string moduleName, BYTE* Mask, char* szMask);

		DWORD FindPatternV2(std::string moduleName, std::string pattern);

		DWORD FindTextPattern(std::string moduleName, char* string);

		class VMTManager
		{
		private:
			DWORD	*CustomTable;
			bool	initComplete;
			DWORD	*OriginalTable;
			DWORD	*Instance;

			int		MethodCount(DWORD* InstancePointer);
			
		public:
			bool	Initialise(DWORD* InstancePointer); 

			DWORD	HookMethod(DWORD NewFunction, int Index);
			void	UnhookMethod(int Index);

			void	RestoreOriginal();
			void	RestoreCustom();

			template<typename T>
			T GetMethod(size_t nIndex)
			{
				return (T)OriginalTable[nIndex];
			}

			DWORD	GetOriginalFunction(int Index);
		};
	};
};

template<typename T>
FORCEINLINE T GetMethod(const void* instance, size_t index)
{
	uintptr_t* vmt = *(uintptr_t**)instance;

	return (T)vmt[index];
}