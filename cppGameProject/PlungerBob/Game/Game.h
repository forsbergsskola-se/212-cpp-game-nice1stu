#pragma once

#include "Level.h"
#include "Player.h"
#include "Framework/Animator.h"

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

	enum EState
	{
		IDLE = 0,
		COUNT_DOWN,
		PRE_START,
		ROUND_STARTED,
		ROUND_ENDED
	};

	CLevel* m_pLevel;

	CPlayer* m_pPlayer;

	CTexture* m_pStartScreenTexture;
	CTexture* m_pCountdownTexture;
	CAnimator* m_pCountdownAnimator;

	float m_CountdownTimerDefault;
	float m_CountdownTimer;


	EState m_State;
};