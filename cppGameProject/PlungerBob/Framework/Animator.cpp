#include "Animator.h"

#include <stdlib.h>

CAnimator::CAnimator(void)
: m_pTexture(nullptr)
, m_ClipQuad({0, 0, 0, 0})
, m_Speed(0.0f)
, m_Advance(0.0f)
, m_NumFrames(0)
, m_StartFrame(0)
, m_EndFrame(0)
, m_FrameWidth(0)
, m_FrameHeight(0)
, m_Row(0)
, m_CurrentFrame(0)
, m_Name("")
, m_Loop(true)
, m_Direction(EDirection::FORWARD)
{

}

CAnimator::~CAnimator(void)
{

}

void CAnimator::Set(CTexture* pTexture, const uint32_t NumFrames, const uint32_t StartFrame, const uint32_t EndFrame, const uint32_t Row, const CVector2D FrameSize, const float Speed, const std::string& rName, const bool Loop, const EDirection Direction)
{
	m_pTexture		= pTexture;
	m_Speed			= Speed;
	m_NumFrames		= NumFrames;
	m_StartFrame	= StartFrame;
	m_EndFrame		= EndFrame;
	m_FrameWidth	= (uint32_t)FrameSize.x;
	m_FrameHeight	= (uint32_t)FrameSize.y;
	m_Row			= Row;
	m_CurrentFrame	= StartFrame;
	m_Name			= rName;
	m_Loop			= Loop;
	m_Direction		= Direction;

	Reset();
}

void CAnimator::Update(const float DeltaTime)
{
	m_Advance += m_Speed * DeltaTime;

	if(m_Advance > 1.0f)
	{
		const bool Forward = (m_Direction == EDirection::FORWARD);

		m_CurrentFrame += (Forward ? 1 : -1);

		if(Forward)
		{
			if(m_CurrentFrame > (int32_t)m_EndFrame)
				m_CurrentFrame = (m_Loop ? m_StartFrame : m_EndFrame);
		}

		else
		{
			if(m_CurrentFrame < (int32_t)m_EndFrame)
				m_CurrentFrame = (m_Loop ? m_StartFrame : m_EndFrame);
		}

		SetClipQuad();

		m_Advance = 0.0f;
	}

	m_pTexture->SetTextureCoords(m_ClipQuad.x, m_ClipQuad.x + m_ClipQuad.w, m_ClipQuad.y, m_ClipQuad.y + m_ClipQuad.h);
}

void CAnimator::Reset(void)
{
	m_Advance = 0.0f;

	m_CurrentFrame = m_StartFrame;

	SetClipQuad();
}

void CAnimator::SetClipQuad(void)
{
	m_ClipQuad.x = m_FrameWidth * m_CurrentFrame;
	m_ClipQuad.y = m_FrameHeight * m_Row;
	m_ClipQuad.w = m_FrameWidth;
	m_ClipQuad.h = m_FrameHeight;
}