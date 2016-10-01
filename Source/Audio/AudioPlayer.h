#pragma once

#include "Module.h"
#include <SDL/SDL_mixer.h>

class AudioPlayer : public Component
{
	public:
		AudioPlayer();
		virtual ~AudioPlayer(){}

	private:
		Audio* audio = nullptr;

	protected:
		virtual void onLoadCallback()
};
