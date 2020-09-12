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

#include "../../Entities/Entities.h"
#include "../../../Menu/Menu.h"

#include "../../Hooks/Hooks.h"
#include "Utilities.h"
#include "RenderManager.h"

class trace_info
{
public:
	trace_info(Vector starts, Vector positions, float times, int userids)
	{
		this->start = starts;
		this->position = positions;
		this->time = times;
		this->userid = userids;
	}

	Vector position;
	Vector start;
	float time;
	int userid;
};



extern std::vector<trace_info> trace_logs;
#define g_pGameEventManager Interfaces::EventManager
class : IGameEventListener2
{
public:
	void start()
	{
		g_pGameEventManager->AddListener(this, "round_start", false);
		g_pGameEventManager->AddListener(this, "play_death", false);

	}
	
};
class CBulletListener
{
	class BulletListener : IGameEventListener2
	{
	public:
		void start()
		{
			g_pGameEventManager->AddListener(this, "player_death", false);
			if (!g_pGameEventManager->AddListener(this, "bullet_impact", false))
			{
				throw std::exception("Failed to register the event");
			}
		}
		void stop()
		{
			g_pGameEventManager->RemoveListener(this);
		}
		void FireGameEvent(IGameEvent* event) override
		{
			CBulletListener::singleton()->OnFireEvent(event);
		}
		int GetEventDebugID(void) override
		{
			return EVENT_DEBUG_ID_INIT /*0x2A*/;
		}
	};
public:
	static CBulletListener* singleton()
	{
		static CBulletListener* instance = new CBulletListener();
		return instance;
	}

	void init()
	{
		_listener.start();
	}

	void OnFireEvent(IGameEvent* event)
	{
		if (!strcmp(event->GetName(), "bullet_impact"))
		{


			auto shooter = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetPlayerForUserID(event->GetInt("userid")));

			Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));
			if (shooter)
				trace_logs.push_back(trace_info(shooter->GetEyePosition(),position, Interfaces::Globals->curtime, event->GetInt("userid")));

			//	}
		}

	}

	void OnStudioRender()
	{
		if (Options::Menu.VisualsTab.BulletTracers.GetState())
		{

			for (unsigned int i = 0; i < trace_logs.size(); i++) {
				IClientEntity* LocalPlayer = (IClientEntity*)Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
				auto *shooter = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetPlayerForUserID(trace_logs[i].userid));

				if (!shooter) return;

				Color color;
				if (shooter == LocalPlayer)
					color = Color(2, 255, 44, 255);
				else
					color = Color(255, 0, 0, 255);

				Hooks::DrawBeamd(trace_logs[i].start, trace_logs[i].position, color);

				trace_logs.erase(trace_logs.begin() + i);
			}
		}
	}

private:
	BulletListener _listener;

	class cbullet_tracer_info
	{
	public:
		cbullet_tracer_info(Vector src, Vector dst, float time, Color color)
		{
			this->src = src;
			this->dst = dst;
			this->time = time;
			this->color = color;
		}

		Vector src, dst;
		float time;
		Color color;
	};

	std::vector<cbullet_tracer_info> logs;
};
