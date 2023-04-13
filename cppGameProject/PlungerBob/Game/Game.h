#pragma once

#include "Level.h"
#include "Player.h"
#include "Toilette.h"

#include "Framework/Random.h"
#include "Framework/Animator.h"

class CGame
{
public:

	typedef std::vector<CToilette*> ToiletteList;

public:

	CGame();
	~CGame();

	bool Create();
	void Destroy();

	void Update(const float Deltatime);

	void Render();
	void RenderDebug();

private:

	void ActivateRandomToilette();
	void OnPlumbingStart(const uint32_t ToiletteID);

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
	CTexture* m_pGoTexture;

	CAnimator* m_pCountdownAnimator;

	CRandom	m_RandomNumberGenerator;

	float m_CountdownTimerDefault;
	float m_CountdownTimer;
	float m_GameStartTimer;

	uint32_t m_CurrentToilette;
	uint32_t m_NumActivatedToilettes;

	EState m_State;

	ToiletteList m_Toilettes;
};