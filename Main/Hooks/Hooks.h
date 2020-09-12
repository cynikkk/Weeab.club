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

#include "../SDK/SDK/Utilities.h"
#include "../../Menu/Interface/Interfaces.h"

extern float last_real;
extern float lineLBY;
extern float lineRealAngle;
extern float lineFakeAngle;
extern float lspeed;
extern float pitchmeme;
extern float lby2;
extern bool DoUnload;
extern bool bGlovesNeedUpdate;
extern int missedLogHits[65];

namespace Hooks
{
	void Initialise();
	void DrawBeamd(Vector src, Vector end, Color color);
	void UndoHooks();


	extern Utilities::Memory::VMTManager VMTPanel; 
	extern Utilities::Memory::VMTManager VMTClient; 
	extern Utilities::Memory::VMTManager VMTClientMode;
	extern Utilities::Memory::VMTManager VMTModelRender;
	extern Utilities::Memory::VMTManager VMTPrediction; 
	extern Utilities::Memory::VMTManager VMTRenderView;
	extern Utilities::Memory::VMTManager VMTEventManager;
	extern Utilities::Memory::VMTManager VMTCreateMove;
};

namespace Resolver
{
	extern bool didhitHS;
	extern bool hitbaim;
	extern bool lbyUpdate;

}


namespace bigboi
{
	extern bool freestand;
	extern int indicator;
	extern int freestandval;
	
}
extern bool warmup;