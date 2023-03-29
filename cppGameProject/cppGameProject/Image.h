#pragma once
class Image
{
	//The image we will load and show on the screen
	SDL_Surface* gHelloWorld = nullptr;
	bool loadMedia();
	bool success;

public:
	Image()
	{
		success = loadMedia();
	}
	~Image();
	bool wasSuccessful() { return success; }
};

