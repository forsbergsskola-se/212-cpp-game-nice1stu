#include "Window.h"
#include <cstdio>
#include <SDL.h>

Window::Window(int width, int height) : success{} {

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	//Create window
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!gWindow)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	//Get window surface
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	success = true;

}

Window::~Window() {
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	//Quit SDL subsystem
	SDL_Quit();
}

void Window::render(Image& image) {
	SDL_Rect rect{ 100, 100, 5, 5 };
	//Apply image
	SDL_BlitSurface(image.getResource(), nullptr, gScreenSurface, &rect);
	//Update the surface
	SDL_UpdateWindowSurface(gWindow);
}