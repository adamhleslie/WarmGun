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
		void changeSoundEffectVolume(int volume);
		void muteSoundEffect();
		void changeBackgroundMusicVolume(int volume);
		void muteBackgroundMusic();

	protected:
		void postLoad() override;

	private:
		Audio* audio = nullptr;
};
