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

#define _CRT_SECURE_NO_WARNINGS

#include "Hacks.h"
#include "../Menu/Interface/Interfaces.h"
#include "../Main/SDK/SDK/RenderManager.h"

#include "../Hacks/Features/Visuals/ESP/ESP.h"
#include "../Hacks/Features/Visuals/Visuals.h"
#include "../Hacks/Features/Aim/Rage/RageBot.h"
#include "../Hacks/Features/Aim/Legit/LegitBot.h"
#include "../Hacks/Misc/MiscHacks.h"

CEsp Esp;
CVisuals Visuals;
CMiscHacks MiscHacks;
CRageBot RageBot;
CLegitBot LegitBot;

void Hacks::SetupHacks()
{
	Esp.Init();
	Visuals.Init();
	MiscHacks.Init();
	RageBot.Init();
	LegitBot.Init();

	hackManager.RegisterHack(&Esp);
	hackManager.RegisterHack(&Visuals);
	hackManager.RegisterHack(&MiscHacks);
	hackManager.RegisterHack(&RageBot);
	hackManager.RegisterHack(&LegitBot);

	hackManager.Ready();
}


void SpecList()
{
	IClientEntity *pLocal = hackManager.pLocal();

	RECT scrn = Render::GetViewport();
	int ayy = 0;

	// Loop through all active entitys
	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{

		// Get the entity
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		player_info_t pinfo;

		// The entity isn't some laggy peice of shit or something
		if (pEntity &&  pEntity != pLocal)
		{
			if (Interfaces::Engine->GetPlayerInfo(i, &pinfo) && !pEntity->IsAlive() && !pEntity->IsDormant())
			{
				HANDLE obs = pEntity->GetObserverTargetHandle();

				if (obs)
				{
					IClientEntity *pTarget = Interfaces::EntList->GetClientEntityFromHandle(obs);
					player_info_t pinfo2;
					if (pTarget)
					{

						if (Interfaces::Engine->GetPlayerInfo(pTarget->GetIndex(), &pinfo2))
						{
							if (strlen(pinfo.name) > 16)
							{

								pinfo.name[12] = 0;
								strcat(pinfo.name, "...");
								RECT TextSize = Render::GetTextSize(Render::Fonts::ESP, pinfo.name);
								RECT nameSize = Render::GetTextSize(Render::Fonts::ESP, pinfo.name);
								Render::Text(scrn.right - TextSize.right - 5, (scrn.top / 4) + (16 * ayy), pTarget->GetIndex() /*== pLocal->GetIndex()*/ ? Color(170, 0, 250, 255) : Color(255, 255, 255, 255), Render::Fonts::ESP, pinfo.name);
								ayy++;
							}
						}

					}
				}

			}
		}
	}

}


void Hacks::DrawHacks()
{
	if (!Options::Menu.VisualsTab.Active.GetState())
		return;


	if (Options::Menu.VisualsTab.SpecList.GetState())
		SpecList();


	hackManager.Draw();
		
}

void Hacks::MoveHacks(CUserCmd * pCmd, bool & bSendPacket)
{
	Vector origView = pCmd->viewangles;
	IClientEntity *pLocal = hackManager.pLocal();
	hackManager.Move(pCmd, bSendPacket);



}

HackManager hackManager;

void HackManager::RegisterHack(CHack* hake)
{
	Hacks.push_back(hake);
	hake->Init();
}

void HackManager::Draw()
{
	if (!IsReady)
		return;

	pLocalInstance = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!pLocalInstance) return;

	for (auto &hack : Hacks)
	{
		hack->Draw();
	}
}

void HackManager::Move(CUserCmd *pCmd,bool &bSendPacket)
{
	if (!IsReady)
		return;

	pLocalInstance = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	if (!pLocalInstance) return;

	for (auto &hack : Hacks)
	{
		hack->Move(pCmd,bSendPacket); 
	}
}

IClientEntity* HackManager::pLocal()
{
	return pLocalInstance;
}

void HackManager::Ready()
{
	IsReady = true;
}