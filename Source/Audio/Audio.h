#pragma once

#include "Module.h"
#include <SDL/SDL_mixer.h>

class Audio : public Module
{
	public:
		Audio();
		virtual ~Audio();

		bool init();
};
