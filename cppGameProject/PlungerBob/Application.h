#pragma once

#include "Singleton.h"

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

	bool			m_Running;

};