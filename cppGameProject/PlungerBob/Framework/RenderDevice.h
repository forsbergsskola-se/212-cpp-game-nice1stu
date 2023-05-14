#pragma once

#include "Singleton.h"
#include "Texture.h"
#include "Window.h"

#include <SDL.h>
#include <string>

class CRenderDevice : public CSingleton<CRenderDevice>
{
public:

	 CRenderDevice								(void);
	~CRenderDevice								(void);

	bool			Create						(const CVector2D& rWindowSize, const std::string& rWindowTitle);
	void			Destroy						(void);

	bool			BeginRender					(void);
	void			EndRender					(void);

	SDL_Texture*	CreateTextureFromSurface	(SDL_Surface* pSurface);
	void			DestroyTexture				(SDL_Texture** pTexture);

	void			RenderCopy					(CTexture* pTexture);
	void			RenderCopy					(CTexture* pTexture, const CVector2D& rPosition);

	void			RenderQuad					(const SDL_FRect& rQuad, const bool Filled);

	void			SetRenderDrawColor			(const SDL_Color& rColor);

	bool			SetWindowTitle				(const std::string& rWindowTitle);

	void			Sleep						(const uint32_t TimeMs);

public:

	CWindow*		GetWindow					(void)	const					{return m_pWindow;}

	SDL_Renderer*	GetRenderer					(void)	const					{return m_pRenderer;}

	SDL_Color&		GetClearColor				(void)	const					{return (SDL_Color&)m_ClearColor;}
	void			SetClearColor				(const SDL_Color& rClearColor)	{m_ClearColor = rClearColor;}

private:

	CWindow*		m_pWindow;

	SDL_Renderer*	m_pRenderer;

	SDL_Color		m_ClearColor;

};