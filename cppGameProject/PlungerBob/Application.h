#pragma once

class CApplication
{
public:

	CApplication();
	~CApplication();

private:

	SDL_Window* m_pWindow;

	SDL_Renderer* m_pRenderer;

};