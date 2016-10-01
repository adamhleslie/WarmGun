#include "Audio.h"

Mix_Chunk *s1 = NULL;
Mix_Chunk *s2 = NULL;
Mix_Chunk *s3 = NULL;
Mix_Chunk *s4 = NULL;
Mix_Chunk *s5 = NULL;

Audio::Audio()
{
    disable();

    bool openStatus = Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    assert(openStatus != -1);
    
	s1 = Mix_LoadWAV( "s1.wav" );
	s2 = Mix_LoadWAV( "s2.wav" );
	s3 = Mix_LoadWAV( "s3.wav" );
	s4 = Mix_LoadWAV( "s4.wav" );
	s5 = Mix_LoadWAV( "s5.wav" );

    assert( s1 != NULL );
    assert( s2 != NULL );
    assert( s3 != NULL );
    assert( s4 != NULL );
    assert( s5 != NULL );
}


int Audio::play_s1()
{
    return Mix_PlayChannel( -1, s1, 1 );
}

int Audio::play_s2()
{
    return Mix_PlayChannel( -1, s2, 1 );
}

int Audio::play_s3()
{
    return Mix_PlayChannel( -1, s3, 1 );
}

int Audio::play_s4()
{
    return Mix_PlayChannel( -1, s4, 1 );
}

int Audio::play_s5()
{
    return Mix_PlayChannel( -1, s5, 1 );
}

Audio::~Audio()
{
    Mix_FreeChunk( s1 );
    Mix_FreeChunk( s2 );
    Mix_FreeChunk( s3 );
    Mix_FreeChunk( s4 );
    Mix_FreeChunk( s5 );

    Mix_CloseAudio();
}


