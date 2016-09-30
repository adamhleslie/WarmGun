#pragma once

#include "Module.h"
#include <SDL/SDL.h>

class Audio : public Module
{
	public:
		Audio();
		virtual ~Audio();

		int  openAudioDevice();
		void playAudio();
		void fill_audio(void *udata, Uint8 *stream, int len);
};
