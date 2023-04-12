#include "Game.h"

#include "Framework/InputHandler.h"

CGame::CGame()
	: m_pLevel(nullptr)
	, m_pPlayer(nullptr)
{
}

CGame::~CGame()
{
}

bool CGame::Create()
{
	m_pLevel = new CLevel;

	if (!m_pLevel->Create())
	{
		printf("Error: Failed to create level\n");

		return false;
	}

	m_pPlayer = new CPlayer;

	if (!m_pPlayer->Create())
	{
		printf("Error: Failed to create player\n");

		return false;
	}

	return true;
}

void CGame::Destroy()
{
	m_pPlayer->Destroy();
	delete m_pPlayer;
	m_pPlayer = nullptr;

	m_pLevel->Destroy();
	delete m_pLevel;
	m_pLevel = nullptr;
}

void CGame::Update(const float Deltatime)
{
	m_pPlayer->HandleInput();
	m_pPlayer->Update(Deltatime);
}

void CGame::Render()
{
	m_pLevel->Render();
	m_pPlayer->Render();
}

void CGame::RenderDebug()
{
	m_pLevel->RenderDebug();
	m_pPlayer->RenderDebug();
}
