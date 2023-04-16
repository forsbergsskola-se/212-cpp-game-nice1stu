#include "Toilette.h"

#include "Framework/RenderDevice.h"

CToilet::CToilet(void)
: m_Position(CVector2D::Zero)
, m_FrameSize(CVector2D::Zero)
, m_TimerDefault(1.5f)
, m_Timer(m_TimerDefault)
, m_State(EState::EMPTY)
, m_Top(false)
, m_Activated(false)
{

}

CToilet::~CToilet(void)
{

}

void CToilet::Create(const CVector2D& rPosition, const CVector2D& rFrameSize, const bool Top)
{
	m_Position = rPosition;

	m_FrameSize = rFrameSize;

	m_Top = Top;
}

void CToilet::Update(const float DeltaTime)
{
	if(!m_Activated || (m_State == EState::FULL))
		return;

	m_Timer -= DeltaTime;

	if(m_Timer <= 0.0f)
	{
		m_Timer = m_TimerDefault;

		m_State++;

		if(m_State > EState::FULL)
			m_State = EState::FULL;
	}
}

void CToilet::Render(CTexture* pWaterTexture)
{
	const uint32_t Left		= (uint32_t)(m_FrameSize.x * m_State);
	const uint32_t Right	= (uint32_t)((m_FrameSize.x * m_State) + m_FrameSize.x);
	const uint32_t Top		= (m_Top ? 0 : (uint32_t)m_FrameSize.y);
	const uint32_t Bottom	= Top + (uint32_t)m_FrameSize.y;

	pWaterTexture->SetTextureCoords(Left, Right, Top, Bottom);

	CRenderDevice::GetInstance().RenderCopy(pWaterTexture, m_Position);
}

void CToilet::RenderDebug(void)
{
	CRenderDevice::GetInstance().SetRenderDrawColor({0, 0, 255, 255});

	const SDL_FRect Quad = {m_Position.x, m_Position.y, m_FrameSize.x, m_FrameSize.y};
	CRenderDevice::GetInstance().RenderQuad(Quad, false);
}

void CToilet::Activate(void)
{
	Reset();

	m_Activated = true;
}

void CToilet::Reset(void)
{
	m_Timer = m_TimerDefault;

	m_State = EState::EMPTY;

	m_Activated = false;
}