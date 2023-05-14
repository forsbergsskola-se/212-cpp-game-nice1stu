#pragma once

#include "Texture.h"

#include <SDL.h>
#include <stdint.h>

class CAnimator
{
public:

	enum EDirection
	{
		FORWARD = 0,
		BACKWARD
	};

public:

	 CAnimator					(void);
	~CAnimator					(void);

	void		Set				(CTexture* pTexture, const uint32_t NumFrames, const uint32_t StartFrame, const uint32_t EndFrame, const uint32_t Row, const CVector2D FrameSize, const float Speed, const std::string& rName, const bool Loop, const EDirection Direction);

	void		Update			(const float DeltaTime);

	void		Reset			(void);

public:

	uint32_t	GetEndFrame		(void) const {return m_EndFrame;}

	int32_t		GetCurrentFrame	(void) const {return m_CurrentFrame;}

private:

	void		SetClipQuad		(void);

private:

	CTexture*	m_pTexture;

	SDL_Rect	m_ClipQuad;

	float		m_Speed;
	float		m_Advance;

	uint32_t	m_NumFrames;
	uint32_t	m_StartFrame;
	uint32_t	m_EndFrame;
	uint32_t	m_FrameWidth;
	uint32_t	m_FrameHeight;
	uint32_t	m_Row;

	int32_t		m_CurrentFrame;

	std::string	m_Name;

	bool		m_Loop;

	EDirection	m_Direction;

};