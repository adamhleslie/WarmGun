#include "AudioPlayer.h"

int currentSoundEffectVolume = 128;
int currentBackgroundMusicVolume = 128;

void AudioPlayer::postLoad ()
{
	audio = getEntity()->getCore()->getModule<Audio>();
	assert(audio);
}

void AudioPlayer::changeSoundEffectVolume(int volume)
{
	currentSoundEffectVolume += volume;
	Mix_Volume(1, currentSoundEffectVolume);
	Mix_Volume(2, currentSoundEffectVolume);
	Mix_Volume(3, currentSoundEffectVolume);
}

void AudioPlayer::muteSoundEffect()
{
	if(currentSoundEffectVolume!=0)
	{
		currentSoundEffectVolume=0;
		Mix_Volume(1,0);
		Mix_Volume(2,0);
		Mix_Volume(3,0);
	}
	else
	{
		currentSoundEffectVolume=128;
		Mix_Volume(1,128);
		Mix_Volume(2,128);
		Mix_Volume(3,128);
	}
}

void AudioPlayer::changeBackgroundMusicVolume(int volume)
{
	currentBackgroundMusicVolume += volume;
	Mix_Volume(4, currentBackgroundMusicVolume);
}

void AudioPlayer::muteBackgroundMusic()
{
	if(currentBackgroundMusicVolume!=0)
	{
		currentBackgroundMusicVolume=0;
		Mix_Volume(4,0);
	}
	else
	{
		currentBackgroundMusicVolume=128;
		Mix_Volume(4,128);
	}
}

int AudioPlayer::playSound(int i)
{
	// switch(i)
	// {
	// 	case 1:
	// 		audio->play_s1();
	// 		break;
	// 	case 2:
	// 		audio->play_s2();
	// 		break;
	// 	case 3:
	// 		audio->play_s3();
	// 		break;
	// 	case 4:
	// 		audio->play_s4();
	// 		break;
	// }
}



