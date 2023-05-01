#include "engine.h"

int init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return 1;
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3);

    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if (window == NULL)
    {
        return 2;
    }

    context = SDL_GL_CreateContext( window );
    if (context == NULL)
    {
        return 3;
    }

    if (SDL_GL_SetSwapInterval( 1 ) < 0 )
    {
        printf("non fatal error: could not set vsync\n");
    }

    glewExperimental = GL_TRUE;
    if ( glewInit() != GLEW_OK )
    {
        return 4;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        return 5;
    }

    if ( TTF_Init() == -1)
    {
        return 6;
    }
    

    return 0;
}


void quit()
{

    TTF_CloseFont( font );

    SDL_DestroyWindow( window );
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int initGL()
{
    GLenum error = GL_NO_ERROR;

    return 0;
}


