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

#include "lin_extp.h"

template<class T, class U>
T fine(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}
void LinearExtrapolations::run()
{
	if (Options::Menu.RageBotTab.extrapolation.GetState())
	{
		auto m_local = hackManager.pLocal();
		if (m_local && m_local->IsAlive()) {
			for (int i = 1; i < Interfaces::Globals->maxClients; i++)
			{
				auto m_entity = Interfaces::EntList->GetClientEntity(i);
				if (!m_entity || m_entity == m_local || m_entity->GetClientClass()->m_ClassID != (int)CSGOClassID::CCSPlayer || !m_entity->IsAlive()) continue;



				float simtime_delta = m_entity->GetSimulationTime() - m_entity->m_flOldSimulationTime();
				int choked_ticks = fine(TIME_TO_TICKS(simtime_delta), 1, 15);
				Vector lastOrig;

				if (lastOrig.Length() != m_entity->GetOrigin().Length())
					lastOrig = m_entity->GetOrigin();

				float delta_distance = (m_entity->GetOrigin() - lastOrig).LengthSqr();
				if (delta_distance > 4096.f)
				{
					Vector velocity_per_tick = m_entity->GetVelocity() * Interfaces::Globals->interval_per_tick;
					auto new_origin = m_entity->GetOrigin() + (velocity_per_tick * choked_ticks);
					m_entity->SetAbsOriginal(new_origin);
				}
			}
		}
	}
}