#include "Application.h"

#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

CApplication::CApplication()
: m_pWindow(nullptr)
, m_pRenderer(nullptr)
, m_Running(true)
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", IMG_GetError());
		return;
	}
	//Create window
	m_pWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!m_pWindow)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!m_pRenderer)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return;
	}

	//TODO: create the game instance
}

CApplication::~CApplication()
{
	// TODO: destroty the game instance

	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = nullptr;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;

	IMG_Quit();

	//Quit SDL subsystems
	SDL_Quit();
}

void CApplication::Run()
{
	while (m_Running)
	{
		Update();
		Render();
	}
}

void CApplication::Update()
{
//	Game.Update();
}

void CApplication::Render()
{
//	Game.Render();
}