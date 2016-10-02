#pragma once

#include "Module.h"
#include <SDL/SDL_mixer.h>
#include "Audio.h"
#include "Component.h"
#include "Entity.h"
#include "Core.h"

class AudioPlayer : public Component
{
	public:
		AudioPlayer();
		virtual ~AudioPlayer(){}
		int playSound(int i);

	private:
		Audio* audio = nullptr;

	protected:
		virtual void onLoadCallback(Entity* entity);
};
