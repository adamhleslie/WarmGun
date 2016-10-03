#include "AudioPlayer.h"

void AudioPlayer::onLoadCallback(Entity* entity)
{
	audio = entity->getCore()->getModule<Audio>();
	assert(audio);
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



