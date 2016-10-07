#include "AudioPlayer.h"

int currentVolume = 128;

void AudioPlayer::postLoad ()
{
	audio = getEntity()->getCore()->getModule<Audio>();
	assert(audio);
}

int AudioPlayer::changeVolume(int volume)
{
	currentVolume += volume;
	if(volume>=0)
	{
		return Mix_Volume(-1, currentVolume);
	}
	else
	{
		return Mix_Volume(-1, currentVolume);
	}
}

int AudioPlayer::muteVolume()
{
	if(currentVolume!=0)
	{
		currentVolume=0;
		return Mix_Volume(-1,0);
	}
	else
	{
		currentVolume=128;
		return Mix_Volume(-1,128);
	}
}

int AudioPlayer::playSound(int i)
{
	switch(i)
	{
		case 1:
			audio->play_s1();
			break;
		case 2:
			audio->play_s2();
			break;
		case 3:
			audio->play_s3();
			break;
		case 4:
			audio->play_s4();
			break;
		case 5:
			audio->play_s5();
			break;
	}
}



