#pragma once
#include <SDL.h>
class Image
{
	//The image we will load and show on screen
	SDL_Surface* gHelloWorld{};
	bool success;
public:
	Image(const char* path);
	~Image();
	bool wasSuccessful() { return success; }
	SDL_Surface* getResource() { return gHelloWorld; }
};

