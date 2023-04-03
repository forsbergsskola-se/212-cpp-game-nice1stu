#pragma once
#include <SDL.h>

class Window
{
	// The window we'll be rendering to
	SDL_Window* window{};

	// The surface contained by the window
	SDL_Surface* screenSurface{};

public:
	Window(int width, int height);
	~Window();

	bool wasSuccessful() { return window != nullptr && screenSurface != nullptr; }

	void render(SDL_Surface* imageSurface);
};
