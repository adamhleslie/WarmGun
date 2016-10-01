#pragma once

#include "Module.h"
#include <SDL/SDL_mixer.h>

class Audio : public Module
{
	public:
		Audio();
		virtual ~Audio();

		static bool init();
		static bool load_files();
		static void clean_up();
		static int  play_sound();
};
