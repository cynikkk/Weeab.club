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

#include "global_count.h"

namespace global_count
{
	int hits[65];
	int shots_fired[65];

	bool didhit;
	bool on_fire;
}


void game_event::on_hurt(IGameEvent * Event)
{
	if (!Event)
		global_count::didhit = false;

	if (!strcmp(Event->GetName(), "player_hurt"))
	{
		int deadfag = Event->GetInt("userid");
		int attackingfag = Event->GetInt("attacker");
		if (Interfaces::Engine->GetPlayerForUserID(attackingfag) == Interfaces::Engine->GetLocalPlayer())
		{
			global_count::didhit = true;
			global_count::on_fire = true;
		}
	}
}
