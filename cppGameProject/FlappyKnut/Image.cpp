#include "Image.h"
#include "SDL.h"
#include <cstdio>

Image::Image(const char* path) : success{} {

	//Load splash image
	gHelloWorld = SDL_LoadBMP(path);
	if (!gHelloWorld)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		return;
	}
	
	success = true;
}

Image::~Image() {
	//Dealloacate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = nullptr;
}