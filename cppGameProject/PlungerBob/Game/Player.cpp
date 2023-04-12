#include "Player.h"

#include "Framework/RenderDevice.h"
#include "Framework/TextureFactory.h"
#include "Framework/InputHandler.h"

CPlayer::CPlayer()
	:m_pTexture (nullptr)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Create()
{
	const CVector2D FrameSize = CVector2D(128.0f, 128.0f);

	m_pTexture = CTextureFactory::GetInstance().CreateTexture("Plumber.png");
	m_pTexture->SetTextureCoords(0, FrameSize.x, 0, FrameSize.y);

	return true;
}

void CPlayer::Destroy()
{
	CTextureFactory::GetInstance().DestroyTexture(m_pTexture->GetName());
}

void CPlayer::HandleInput()
{

}

void CPlayer::Render()
{
	CRenderDevice::GetInstance().RenderCopy(m_pTexture);
}

void CPlayer::RenderDebug()
{

}
