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

#include "../Hacks.h"

Vector GetAutostrafeView();

class CMiscHacks : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
	void FakeWalk0(CUserCmd * pCmd, bool & bSendPacket);

private:
	
	void AutoPistol(CUserCmd * pCmd);


	void SlowMo(CUserCmd * pCmd, bool & bSendPacket);
	void Namespam();
	void NoName();
	void NameSteal();
	
	void AutoJump(CUserCmd *pCmd);
	void RageStrafe(CUserCmd *pCmd);
	void left2();

	void PostProcces();

	void SlowMo2(CUserCmd * pCmd, bool & bSendPacket);

	int CircleFactor = 0;
	
}; extern CMiscHacks* g_Misc;



