#include "Audio.h"

Mix_Chunk *s1 = NULL;
Mix_Chunk *s2 = NULL;
Mix_Chunk *s3 = NULL;
Mix_Chunk *s4 = NULL;
Mix_Chunk *s5 = NULL;

Audio::Audio ()
{
	stopUpdating();

	bool openStatus = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	assert(openStatus != -1);
	
	s1 = Mix_LoadWAV("Media/Audio/s1.wav");
	s2 = Mix_LoadWAV("Media/Audio/s2.wav");
	s3 = Mix_LoadWAV("Media/Audio/s3.wav");
	s4 = Mix_LoadWAV("Media/Audio/s4.wav");

	assert( s1 != NULL );
	assert( s2 != NULL );
	assert( s3 != NULL );
	assert( s4 != NULL );

	// play_s4();
}

Audio::~Audio ()
{
	Mix_FreeChunk( s1 );
	Mix_FreeChunk( s2 );
	Mix_FreeChunk( s3 );
	Mix_FreeChunk( s4 );

	Mix_CloseAudio();
}

int Audio::play_s1 ()
{
	return Mix_PlayChannel( 1, s1, 0 );
}

int Audio::play_s2 ()
{
	return Mix_PlayChannel( 2, s2, 0 );
}

int Audio::play_s3 ()
{
	return Mix_PlayChannel( 3, s3, 0 );
}

int Audio::play_s4 ()
{
    return Mix_PlayChannel( 4, s4, 10 );
}
