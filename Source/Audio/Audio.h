#pragma once

#include "Module.h"
#include <cassert>
#include <SDL/SDL_mixer.h>

class Audio : public Module
{
	public:
		Audio();
		virtual ~Audio();

		int play_s1();
		int play_s2();
		int play_s3();
		int play_s4();
};
