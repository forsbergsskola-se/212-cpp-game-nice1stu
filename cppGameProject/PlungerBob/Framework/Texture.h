#pragma once

#include "Vector2D.h"

#include <SDL.h>
#include <string>

class CTexture
{
	friend class CTextureHandler;

public:

	 CTexture								(void);
	~CTexture								(void);

	bool				Create				(const std::string& rFileName);
	void				Destroy				(void);

	void				SetTextureCoords	(const uint32_t Left, const uint32_t Right, const uint32_t Top, const uint32_t Bottom);

public:

	SDL_Texture*		GetTexture			(void)	const						{return m_pTexture;}

	SDL_Rect*			GetClipQuad			(void)	const						{return m_pClipQuad;}

	SDL_RendererFlip	GetFlipMethod		(void)	const						{return m_FlipMethod;}
	void				SetFlipMethod		(const SDL_RendererFlip FlipMethod)	{m_FlipMethod = FlipMethod;}

	CVector2D&			GetPosition			(void)	const						{return (CVector2D&)m_Position;}
	void				SetPosition			(const CVector2D& rPosition)		{m_Position = rPosition;}

	CVector2D&			GetSize				(void)	const						{return (CVector2D&)m_Size;}
	void				SetSize				(const CVector2D& rSize)			{m_Size = rSize;}

	float				GetAngle			(void)	const						{return m_Angle;}
	void				SetAngle			(const float Angle)					{m_Angle = Angle;}

	std::string&		GetName				(void)	const						{return (std::string&)m_Name;}

private:

	SDL_Texture*		m_pTexture;

	SDL_Rect*			m_pClipQuad;

	SDL_RendererFlip	m_FlipMethod;

	CVector2D			m_Position;
	CVector2D			m_Size;

	float				m_Angle;

	uint32_t			m_ReferenceCount;

	std::string			m_Name;

};