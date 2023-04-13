#pragma once

#include "Framework/Texture.h"
#include "Framework/Vector2D.h"

class CToilette
{
public:

	enum EState
	{
		EMPTY = 0,
		NORMAL,
		HALF_FULL,
		FULL
	};

public:

	 CToilette					(void);
	~CToilette					(void);

	void		Create			(const CVector2D& rPosition, const CVector2D& rFrameSize, const bool Top);

	void		Update			(const float DeltaTime);

	void		Render			(CTexture* pWaterTexture);
	void		RenderDebug		(void);

	void		Activate		(void);

	void		Reset			(void);

public:

	uint32_t	GetState		(void) const {return m_State;}

	bool		GetActivated	(void) const {return m_Activated;}

private:

	CVector2D	m_Position;
	CVector2D	m_FrameSize;

	float		m_TimerDefault;
	float		m_Timer;

	uint32_t	m_State;

	bool		m_Top;
	bool		m_Activated;

};