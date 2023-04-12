#include "Level.h"
#include "Framework/TextureFactory.h"
#include "Framework/RenderDevice.h"

CLevel::CLevel()
: m_pTexture(nullptr)
{
}

CLevel::~CLevel()
{
}

bool CLevel::Create()
{
	m_pTexture = CTextureFactory::GetInstance().CreateTexture("Room.png");
	return false;
}

void CLevel::Destroy()
{
	CTextureFactory::GetInstance().DestroyTexture(m_pTexture->GetName());
}

void CLevel::Render()
{
	CRenderDevice::GetInstance().RenderCopy(m_pTexture);
}

void CLevel::RenderDebug()
{
}
