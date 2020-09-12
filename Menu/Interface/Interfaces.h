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

#include <d3d9.h>

#include "../../Includes/CommonIncludes.h"
#include "../../Main/SDK/SDK.h"
#include "../../Main/SDK/SDK/CClientState.h"
#include "../../Hacks/Features/Visuals/Glow/glow_outline_effect.h"
#include "../../Main/SDK/SDK/IClientMode.h"
#include "../../Main/SDK/SDK/CUtlVector.h"

class IMoveHelper : public Interface
{
public:
	void SetHost(IClientEntity* pEnt)
	{
		typedef void(__thiscall* SetHostFn)(void*, IClientEntity*);
		return VFunc<SetHostFn>(1)(this, pEnt);
	}
};

class IPrediction : public Interface
{
public:
	void	SetupMove(IClientEntity *player, CUserCmd *pCmd, IMoveHelper *pHelper, void *move)
	{
		typedef void(__thiscall* SetupMoveFn)(void*, IClientEntity*, CUserCmd*, IMoveHelper*, void*);
		return VFunc<SetupMoveFn>(20)(this, player, pCmd, pHelper, move);
	}

	void	FinishMove(IClientEntity *player, CUserCmd *pCmd, void *move)
	{
		typedef void(__thiscall* FinishMoveFn)(void*, IClientEntity*, CUserCmd*, void*);
		return VFunc<FinishMoveFn>(21)(this, player, pCmd, move);
	}

};

class IGameMovement : public Interface
{
public:
	void ProcessMovement(IClientEntity *pPlayer, void *pMove)
	{
		typedef void(__thiscall* ProcessMovementFn)(void*, IClientEntity*, void*);
		return VFunc<ProcessMovementFn>(1)(this, pPlayer, pMove);
	}

	void StartTrackPredictionErrors(IClientEntity *pPlayer)
	{
		typedef void(__thiscall *o_StartTrackPredictionErrors)(void*, void*);
		return VFunc<o_StartTrackPredictionErrors>(3)(this, pPlayer);
	}

	void FinishTrackPredictionErrors(IClientEntity *pPlayer)
	{
		typedef void(__thiscall *o_FinishTrackPredictionErrors)(void*, void*);
		return VFunc<o_FinishTrackPredictionErrors>(4)(this, pPlayer);
	}
};

namespace Interfaces
{
	void Initialise();
	extern IBaseClientDLL* Client;
	extern IVEngineClient* Engine;
	extern IPanel* Panels;
	extern IClientEntityList* EntList;
	extern ISurface* Surface;
	extern IVDebugOverlay* DebugOverlay;
	extern IClientModeShared *ClientMode;
	extern CGlobalVarsBase *Globals;
	extern DWORD *Prediction;
	extern CMaterialSystem* MaterialSystem;
	extern CVRenderView* RenderView;
	extern IDirect3DDevice9 *g_pD3DDevice9;
	extern IVModelRender* ModelRender;
	extern CGlowObjectManager* m_pGlowObjManager;
	extern CModelInfo* ModelInfo;
	extern HWND window;
	extern IInputSystem* m_iInputSys;
	extern CUtlVectorSimple *g_ClientSideAnimationList;
	extern IEngineTrace* Trace;
	extern IPhysicsSurfaceProps* PhysProps;
	extern ICVar *CVar;
	extern CInput* pInput;
	extern IGameEventManager2 *EventManager;
	extern HANDLE __FNTHANDLE;
	extern IVEffects* m_pEffects;
	extern IVEffects* m_pEffects;
	extern IMoveHelper* MoveHelper;
	extern IPrediction *Prediction1;
	extern CClientState* m_pClientState;
	extern IGameMovement* GameMovement;
	extern IViewRenderBeams* g_pViewRenderBeams;
};