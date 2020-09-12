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

#include "../../Hacks/Misc/MiscDefinitions.h"
#include "../SDK/SDK/ClientRecvProps.h"
#include "../Offsets/Offsets.h"

class IBaseClientDLL
{
public:

	ClientClass * GetAllClasses(void)
	{
		typedef ClientClass* (__thiscall* OriginalFn)(PVOID); //Anything inside a VTable is a __thiscall unless it completly disregards the thisptr. You can also call them as __stdcalls, but you won't have access to the __thisptr.
		return call_vfunc<OriginalFn>(this, Offsets::VMT::CHL_GetAllClasses)(this); //Return the pointer to the head CClientClass.
	}
};