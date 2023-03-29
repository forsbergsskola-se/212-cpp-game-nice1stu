/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "../cppGameProject/Window.h"
#include "../cppGameProject/Image.h"
#include "../02_getting_an_image_on_the_screen/02_getting_an_image_on_the_screen.cpp"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Frees media and shuts down SDL
void close();

int main(int argc, char* args[])
{
	Window window{ SCREEN_WIDTH, SCREEN_HEIGHT };

	//Start up SDL and create window
	if (!window.wasSuccessful())
		{
			printf("Failed to initialize!\n");
			return -1;
		}
	
	//Load media
	Image image{};
		if (!image.wasSuccessful())
		{
			printf("Failed to load media!\n");
			return -1;
		}

		//Apply the image
		SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

		//Update the surface
		SDL_UpdateWindowSurface(gWindow);

		//Hack to get window to stay up
		SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }

	return 0;
}