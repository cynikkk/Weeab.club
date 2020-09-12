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
#include "../SDK.h"

#define MOVING_MINIMUM_SPEED 0.5f //stand anim will be triggered instead of slow playback, walk anim
#define MAIN_IDLE_SEQUENCE_LAYER 0
#define AIMSEQUENCE_LAYER 1
#define NUM_AIMSEQUENCE_LAYERS 4

class LegAnimType_t {

};
class CModAnimConfig {
public: 
	float m_flMaxBodyYawDegrees;
	LegAnimType_t m_LegAnimType;
	bool m_bUseAimSequences;
};
enum {
	TURN_NONE = 0,
	TURN_LEFT,
	TURN_RIGHT
};

