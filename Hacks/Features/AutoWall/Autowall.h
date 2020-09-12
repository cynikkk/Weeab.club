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
#include "../../../Menu/Interface/Interfaces.h"
struct FireBulletData
{
	FireBulletData(const Vector &eye_pos)
		: src(eye_pos)
	{
	}

	Vector           src;
	trace_t          enter_trace;
	Vector           direction;
	CTraceFilter    filter;
	float           trace_length;
	float           trace_length_remaining;
	float           current_damage;
	int             penetrate_count;
};
bool CanHit(const Vector &point, float *damage_given);
bool trace_autowallable(float& dmg);
//bool SimulateFireBullet(IClientEntity * ent, IClientEntity *local, C_BaseCombatWeapon *weapon, FireBulletData &data);

namespace cut_wrists
{
	extern bool yes;
}

