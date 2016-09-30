#include "Audio.h"

//The music that will be played
Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *scratch = NULL;
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;

Audio::Audio()
{
}

Audio::~Audio ()
{
}

bool Audio::init()
{
    // //Initialize all SDL subsystems
    // if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    // {
    //     return false;    
    // }
    
    // //Set up the screen
    // screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    // //If there was an error in setting up the screen
    // if( screen == NULL )
    // {
    //     return false;    
    // }
    
    // //Initialize SDL_ttf
    // if( TTF_Init() == -1 )
    // {
    //     return false;    
    // }
    
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;    
    }
    
    // //Set the window caption
    // SDL_WM_SetCaption( "Monitor Music", NULL );
    
    //If everything initialized fine
    return true;
}


