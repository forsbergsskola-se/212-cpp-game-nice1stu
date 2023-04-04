#pragma once

#include "Game/Game.h"
#include "Framework/Singleton.h"

#include <SDL.h>

class CApplication : public CSingleton<CApplication>
{
public:

	 CApplication();
	~CApplication();

	void Run();

	void Update();
	void Render();

	void Quit() { m_Running = false; }

private:

	SDL_Window*		m_pWindow;

	SDL_Renderer*	m_pRenderer;

	CGame*			m_pGame;

	bool			m_Running;

};