#pragma once
#include "Image.h"
class Window
{
	//The window we'll be rendering to
	SDL_Window* gWindow = nullptr;

	//The surface contained by the window
	SDL_Surface* gScreenSurface = nullptr;

	//Whether window startup was successful
	bool success;

public:
	Window(int width, int height);
	~Window();
	bool wasSuccessful() { return success; }
	void render(Image& image);
};

