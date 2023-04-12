#include "Game.h"

#include "../Framework/InputHandler.h"
#include "Framework/TextureFactory.h"

CGame::CGame()
	: m_pTexture(nullptr)
{
}

CGame::~CGame()
{
}

bool CGame::Create()
{
	m_pTexture = CTextureFactory::GetInstance().CreateTexture("SpaceshipToilet.bmp");
	return true;
}

void CGame::Destroy()
{

}

void CGame::Update(const float Deltatime)
{
	// TODO: move the input handling to the player class

	/*
	if (CInputHandler::GetInstance().KeyPressed(SDL_SCANCODE_LEFT))
	{
		printf("Key left was pressed\n");
	}

	else if (CInputHandler::GetInstance().KeyReleased(SDL_SCANCODE_LEFT))
	{
		printf("Key left was released\n");
	}
	*/
}

void CGame::Render()
{

}

void CGame::RenderDebug()
{
}
