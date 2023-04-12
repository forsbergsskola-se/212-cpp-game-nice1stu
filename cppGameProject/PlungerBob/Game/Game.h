#pragma once

#include "Level.h"

class CGame
{
public:

	CGame();
	~CGame();

	bool Create();
	void Destroy();

	void Render();
	void RenderDebug();

private:
	CLevel* m_pLevel;
};