#pragma once

#include "Framework/Texture.h"

#include <SDL.h>
#include <vector>

class CLevel
{
public:

	typedef std::vector<SDL_FRect> QuadVector;

public:

	 CLevel									(void);
	~CLevel									(void);

	bool				Create				(void);
	void				Destroy				(void);

	void				Render				(void);
	void				RenderDebug			(void);

public:

	const QuadVector&	GetCollisionQuads	(void) const {return m_CollisionQuads;}
	const QuadVector&	GetToiletteQuads	(void) const {return m_ToiletteQuads;}
	const QuadVector&	GetTriggerQuads		(void) const {return m_TriggerQuads;}

private:

	CTexture*	m_pTexture;

	QuadVector	m_CollisionQuads;
	QuadVector	m_ToiletteQuads;
	QuadVector	m_TriggerQuads;

};