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
		AudioPlayer() {}
		~AudioPlayer() {}
		int playSound(int i);

	private:
		Audio* audio = nullptr;

	protected:
		void onLoadCallback(Entity* entity) override;
};
