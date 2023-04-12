#pragma once

#include "Vector2D.h"

#include <SDL.h>
#include <string>

class CWindow
{
public:

	 CWindow						(void);
	~CWindow						(void);

	bool			Create			(const CVector2D& rSize, const std::string& rTitle);
	void			Destroy			(void);

	bool			SetTitle		(const std::string& rTitle);

public:

	SDL_Window*		GetSDLWindow	(void) const {return m_pWindow;}

	CVector2D&		GetPosition		(void) const {return (CVector2D&)m_Position;}
	CVector2D&		GetCenter		(void) const {return (CVector2D&)m_Center;}
	CVector2D&		GetSize			(void) const {return (CVector2D&)m_Size;}

private:

	SDL_Window*	m_pWindow;

	CVector2D	m_Position;
	CVector2D	m_Center;
	CVector2D	m_Size;

};