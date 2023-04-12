#include "Game.h"

#include "Framework/InputHandler.h"

CGame::CGame()
: m_pLevel(nullptr)
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

	return true;
}

void CGame::Destroy()
{
	m_pLevel->Destroy();
	delete m_pLevel;
	m_pLevel = nullptr;
}


void CGame::Render()
{
	m_pLevel->Render();
}

void CGame::RenderDebug()
{
}
