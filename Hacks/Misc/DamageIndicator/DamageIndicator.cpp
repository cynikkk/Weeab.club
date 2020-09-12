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

#include "DamageIndicator.h"
#include "../../Hacks.h"
#include "../../../Menu/Interface/Interfaces.h"
#include "../../../Main/SDK/SDK/RenderManager.h"

DamageIndicators damage_indicators;

void DamageIndicators::paint() {
	auto m_local = hackManager.pLocal();


	float current_time = m_local->GetTickBase() * Interfaces::Globals->interval_per_tick;

	for (int i = 0; i < data.size(); i++) {
		if (data[i].flEraseTime < current_time) {
			data.erase(data.begin() + i);
			continue;
		}

		if (!data[i].bInitialized) {
			data[i].Position = data[i].Player->GetHeadPos();
			data[i].bInitialized = true;
		}

		if (current_time - data[i].flLastUpdate > 0.0001f) {
			data[i].Position.z -= (0.1f * (current_time - data[i].flEraseTime));
			data[i].flLastUpdate = current_time;
		}

		Vector screen_pos;

		if (Render::TransformScreen(data[i].Position, screen_pos)) {
			Render::Text2(screen_pos.x, screen_pos.y, std::to_string(data[i].iDamage).c_str(), Render::Fonts::ESP, Color(255, 255, 255, 255));
		}
	}
}