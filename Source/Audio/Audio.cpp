#include "Audio.h"

// //The music that will be played
// Mix_Music *music = NULL;

//The sound effects that will be used
Mix_Chunk *scratch = NULL;
// Mix_Chunk *high = NULL;
// Mix_Chunk *med = NULL;
// Mix_Chunk *low = NULL;

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

bool Audio::load_files()
{
    // //Load the background image
    // background = load_image( "background.png" );
    
    // //Open the font
    // font = TTF_OpenFont( "lazy.ttf", 30 );
    
    // //If there was a problem in loading the background
    // if( background == NULL )
    // {
    //     return false;    
    // }
    
    // //If there was an error in loading the font
    // if( font == NULL )
    // {
    //     return false;
    // }
    
    // //Load the music
    // music = Mix_LoadMUS( "beat.wav" );
    
    // //If there was a problem loading the music
    // if( music == NULL )
    // {
    //     return false;    
    // }

    // // Load the sound effects
    scratch = Mix_LoadWAV( "scratch.wav" );
    // high = Mix_LoadWAV( "high.wav" );
    // med = Mix_LoadWAV( "medium.wav" );
    // low = Mix_LoadWAV( "low.wav" );
    
    //If there was a problem loading the sound effects
    if( ( scratch == NULL ) )//|| ( high == NULL ) || ( med == NULL ) || ( low == NULL ) )
    {
        return false;    
    }
    
    //If everything loaded fine
    return true;    
}

void clean_up()
{
    // //Free the surfaces
    // SDL_FreeSurface( background );
    
    //Free the sound effects
    Mix_FreeChunk( scratch );
    // Mix_FreeChunk( high );
    // Mix_FreeChunk( med );
    // Mix_FreeChunk( low );
    
    // //Free the music
    // Mix_FreeMusic( music );
    
    // //Close the font
    // TTF_CloseFont( font );
    
    //Quit SDL_mixer
    Mix_CloseAudio();
    
    // //Quit SDL_ttf
    // TTF_Quit();
    
    // //Quit SDL
    // SDL_Quit();
}

int Audio::play_sound()
{
    return Mix_PlayChannel( -1, scratch, 0 );
}



