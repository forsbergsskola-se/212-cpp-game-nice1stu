#pragma once

#include "Framework/Texture.h"
#include "Framework/Animator.h"
#include "Framework/Vector2D.h"
#include <functional>
#include <vector>

class CPlayer
{
public:

	typedef std::vector<SDL_FRect> QuadVector;
	typedef std::function<void(const uint32_t ToiletteID)> PlumbingStartCB;

public:

	CPlayer();
	~CPlayer();

	bool Create();
	void Destroy();

	void HandleInput();
	void Update(const QuadVector& rCollisionQuad, const QuadVector& rToiletteQuads, const QuadVector& rTriggerQuads, const float Deltatime);

	void Render();
	void RenderDebug();

	void PlumbingFinished();

public:

	void SetPlumbingStartCallback(PlumbingStartCB pPlumbingStartCallback)
	{
		m_pPlumbingStartCallback = pPlumbingStartCallback;
	}

private:

	void CheckTriggers(const QuadVector& rTriggerQuads);
	void ResolveXCollision(const SDL_FRect& LevelCollisionQuad, const CVector2D& MoveAmount);
	void ResolveYCollision(const SDL_FRect& LevelCollisionQuad, const CVector2D& MoveAmount);
	void ActivateIdleAnimation();
	void ActivateRunningAnimation();

private:
	CTexture* m_pTexture;

	CVector2D m_Position;
	CVector2D m_Velocity;
	CVector2D m_Speed;
	CVector2D m_CollisionQuadOffset;

	CAnimator* m_pPlayerAnimatorCurrent;
	CAnimator* m_pPlayerAnimatorIdle;
	CAnimator* m_pPlayerAnimatorRunning;

	PlumbingStartCB m_pPlumbingStartCallback;

	uint32_t m_CurrentTRiggerID;


	enum EPLayerState
	{
		IDLE = 0,
		RUNNING_LEFT,
		RUNNING_RIGHT,
		RUNNING_UP,
		RUNNING_DOWN
	};

	uint32_t m_HorizontalDirection;
	uint32_t m_VerticalDirection;
	uint32_t m_LookDirection;

	bool m_Plumbing;

	SDL_FRect m_CollisionQuad;
};