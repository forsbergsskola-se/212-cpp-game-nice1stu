#include "Game.h"

CGame::CGame()
{
}

CGame::~CGame()
{
}

bool CGame::Create()
{


	return true;
}

void CGame::Destroy()
{

}

void CGame::Update()
{
	// TODO: move the input handling to the player class

	/*
	if (CInputHandler::GetInstance().KeyHeld(SDL_SCANCODE_LEFT))
	{
		// MOve the player to the left
	}

	else if (CInputHandler::GetInstance().KeyHeld(SDL_SCANCODE_RIGHT))
	{
		// MOve the player to the right
	}
	*/
}

void CGame::Render()
{

}