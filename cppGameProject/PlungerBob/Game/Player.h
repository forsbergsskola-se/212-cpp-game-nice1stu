#pragma once

#include "Framework/Texture.h"
#include "Framework/Animator.h"

class CPlayer
{
public:

	CPlayer();
	~CPlayer();

	bool Create();
	void Destroy();

	void HandleInput();
	void Update(const float Deltatime);

	void Render();
	void RenderDebug();

private:
	CTexture* m_pTexture;

	CVector2D m_Position;
	CVector2D m_Velocity;
	CVector2D m_Speed;

	CAnimator* m_pPlayerAnimatorIdle;
	CAnimator* m_pPlayerAnimatorRunning;

	enum PLayerState
	{
		IDLE = 0,
		RUNNING_LEFT,
		RUNNING_RIGHT,
		RUNNING_UP,
		RUNNING_DOWN
	};

	int m_HorizontalDirection;
	int m_VerticalDirection;
};