#include "Application.h"

#include <SDL.h>
#include <iostream>

CApplication::CApplication()
: m_pWindow(nullptr)
, m_pRenderer(nullptr)

{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	//Create window
	m_pWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!m_pWindow)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}


}

CApplication::~CApplication()
{
	//Quit SDL subsystems
	SDL_Quit();
}