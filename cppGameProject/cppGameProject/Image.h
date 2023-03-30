#pragma once
#include <SDL.h>

class Image
{
	//The image we will load and show on the screen
	SDL_Surface* imageSurface{};
	bool success;

public:
	Image(const char* path);
	~Image();
	bool wasSuccessful() { return success; }
	SDL_Surface* getResource() { return imageSurface; }
};

