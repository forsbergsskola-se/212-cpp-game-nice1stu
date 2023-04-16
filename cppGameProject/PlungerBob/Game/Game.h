#pragma once

#include "Level.h"
#include "Player.h"
#include "Toilette.h"

#include "Framework/Animator.h"
#include "Framework/Random.h"

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

	void Reset();
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

private:

	CLevel* m_pLevel;

	CPlayer* m_pPlayer;

	CTexture* m_pStartScreenTexture;
	CTexture* m_pCountdownTexture;
	CTexture* m_pGoTexture;
	CTexture* m_pWaterTexture;
	CTexture* m_pPlungerTexture;
	CTexture* m_pEndScreenTexture;

	CAnimator* m_pCountdownAnimator;
	CAnimator* m_pPlumbingAnimator;

	CRandom	m_RandomNumberGenerator;

	float m_CountdownTimerDefault;
	float m_CountdownTimer;
	float m_PreStartTimerDefault;
	float m_PreStartTimer;
	float m_ActivationTimerDefault;
	float m_ActivationTimer;
	float m_PlumbingTimerDefault;
	float m_PlumbingTimer;
	float m_EndScreenTimerDefault;
	float m_EndScreenTimer;

	uint32_t m_CurrentToilette;
	uint32_t m_NumActivatedToilettes;

	bool m_PlumbingStarted;

	EState m_State;

	ToiletteList m_Toilettes;
};