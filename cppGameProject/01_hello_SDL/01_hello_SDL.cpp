#include <SDL.h>
#include <stdio.h>
#include "../cppGameProject/Window.h"
#include "../cppGameProject/Image.h"
#include <map>
#include <memory>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

std::map<SDL_KeyCode, Image> surfaceMap = 
{
	{SDL_KeyCode::SDLK_UP, Image{"img/up.bmp"}},
	{SDL_KeyCode::SDLK_DOWN, Image{"img/down.bmp"}},
	{SDL_KeyCode::SDLK_LEFT, Image{"img/left.bmp"}},
	{SDL_KeyCode::SDLK_RIGHT, Image{"img/right.bmp"}},
};

 const char* fallbackSurface { "img/press.bmp" };

int main(int argc, char* args[])
{
	Window window{ SCREEN_WIDTH, SCREEN_HEIGHT };
	if (!window.wasSuccessful())
		{
			printf("Failed to initialize!\n");
			return -1;
		}
	
	auto image = std::make_unique<Image>(fallbackSurface);
		if (!image->wasSuccessful())
		{
			printf("Failed to load media!\n");
			return -1;
		}

	SDL_Event e; bool quit = false;
	while (quit == false)
	{
		while (SDL_PollEvent(&e))
		{ 
			switch (e.type)
			{
				case SDL_QUIT:
				{
					quit = true;
				} break;

				case SDL_KEYDOWN:
				{
					if (auto result = surfaceMap.find((SDL_KeyCode)e.key.keysym.sym); result != surfaceMap.end())
					{
						auto value = *result;
						auto imageName = value.second;
						image = std::make_unique<Image>(imageName);
						if (!image->wasSuccessful())
						{
							printf("Failed to load media!\n");
							return -1;
						}
					}
					else
					{
						image = std::make_unique<Image>(fallbackSurface);
							if (!image->wasSuccessful())
							{
								printf("Failed to load media!\n");
								return -1;
							}
					}
				}break;
			}
		}
		window.render(image.get());
	}
	return 0;
}