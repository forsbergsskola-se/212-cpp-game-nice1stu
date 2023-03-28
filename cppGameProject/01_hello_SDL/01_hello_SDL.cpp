/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window {};
	
	//The surface contained by the window
	SDL_Surface* screenSurface {};

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ))
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( !window )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			return -1;
		}
		//Get window surface
		screenSurface = SDL_GetWindowSurface( window );
		
		//Fill the surface white
		SDL_FillRect( screenSurface, nullptr, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
		//Update the surface
		SDL_UpdateWindowSurface( window );
           
        //Hack to get window to stay up
        SDL_Event e; bool quit = false;
		while( !quit )
		{
			while( SDL_PollEvent( &e ) )
			{
				if( e.type == SDL_QUIT )
					quit = true;
			}
		}
		
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
