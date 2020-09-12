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

#include "autodefuse.h"

void ADefuse(CUserCmd* cmd) {
	if (!Options::Menu.MiscTab.AutoDefuse.GetState())
		return;
	IClientEntity* localplayer = (IClientEntity*)Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!localplayer || !localplayer->IsAlive())
		return;
	if (localplayer->GetTeamNum() != 3)
		return;
	CCSBomb* bomb = nullptr;
	for (int i = 1; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		IClientEntity* entity = Interfaces::EntList->GetClientEntity(i);
		if (!entity)
			continue;
		if (entity->GetClientClass()->m_ClassID == 108)
		{
			bomb = (CCSBomb*)entity;
			break;
		}
		if (!bomb || bomb->IsBombDefused())
			return;
		float flBlow = bomb->GetC4BlowTime();
		auto local = hackManager.pLocal();
		float lifetime = flBlow - (Interfaces::Globals->interval_per_tick * local->GetTickBase());
		if (localplayer->HasDefuser() && lifetime > 5.5f)
			return;
		if (!localplayer->HasDefuser() && lifetime > 10.5f)
			return;
		if (bomb->IsBombDefused())
			return;
		float distance = localplayer->m_VecORIGIN().DistTo(bomb->GetAbsOrigin());
		if (distance <= 75.0f)
			cmd->buttons |= IN_USE;
	}
}