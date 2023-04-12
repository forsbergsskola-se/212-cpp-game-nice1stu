#include "Player.h"

#include "Framework/RenderDevice.h"
#include "Framework/TextureFactory.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Create()
{
	//m_pPlayer = CTextureFactory::GetInstance().CreateTexture("Plumber.png");
	m_pPlayer = new CPlayer;

	if (!m_pPlayer->Create())
	{
		printf("Error: Failed to create level\n");

		return false;
	}

	return true;
}

void CPlayer::Destroy()
{
	m_pPlayer->Destroy();
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void CPlayer::Render()
{
	m_pPlayer->Render();
}

void CPlayer::RenderDebug()
{
	m_pPlayer->RenderDebug();
}
