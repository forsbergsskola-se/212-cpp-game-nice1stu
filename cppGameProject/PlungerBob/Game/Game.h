#pragma once

#include "Level.h"
#include "Player.h"

class CGame
{
public:

	CGame();
	~CGame();

	bool Create();
	void Destroy();

	void Update(const float Deltatime);

	void Render();
	void RenderDebug();

private:
	CLevel* m_pLevel;
	CPlayer* m_pPlayer;
};