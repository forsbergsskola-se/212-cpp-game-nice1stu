#include "Application.h"

#include "Framework/InputHandler.h"

#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

CApplication::CApplication()
: m_pWindow(nullptr)
, m_pRenderer(nullptr)
, m_pGame(nullptr)
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

	CInputHandler::Initialize();

	m_pGame = new CGame;
	if (!m_pGame->Create())
	{
		printf("Error: Failed to create game\n");
		return;
	}
}

CApplication::~CApplication()
{
	m_pGame->Destroy();
	delete m_pGame;
	m_pGame = nullptr;

	CInputHandler::Deinitialize();

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
	SDL_Event Event;

	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
			case SDL_QUIT:
			{
				m_Running = false;

				break;
			}

			default:
				break;
		}
	}

	CInputHandler::GetInstance().Update();

	m_pGame->Update();
}

void CApplication::Render()
{
	m_pGame->Render();
}