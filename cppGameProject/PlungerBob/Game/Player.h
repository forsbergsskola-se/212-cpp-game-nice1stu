#pragma once

#include "Framework/Animator.h"
#include "Framework/Texture.h"
#include "Framework/Vector2D.h"

#include <functional>
#include <vector>

class CPlayer
{
public:

	typedef std::vector<SDL_FRect>							QuadVector;
	typedef std::function<void(const uint32_t ToiletteID)>	PlumbingStartCB; // Function pointer

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

	void Reset();

public:

	void SetPlumbingStartCallback(PlumbingStartCB pPlumbingStartCallback) {m_pPlumbingStartCallback = pPlumbingStartCallback;}

private:

	void CheckTriggers(const QuadVector& rTriggerQuads);
	void ResolveXCollision(const SDL_FRect& LevelCollisionQuad, const CVector2D& MoveAmount);
	void ResolveYCollision(const SDL_FRect& LevelCollisionQuad, const CVector2D& MoveAmount);
	void ActivateAnimation(CAnimator* pAnimator);

private:

	enum EState
	{
		IDLE = 0,
		RUNNING_LEFT,
		RUNNING_RIGHT,
		RUNNING_UP,
		RUNNING_DOWN
	};

private:

	// A function pointer that's pointing to a function that will be called whenever the player starts a toilette plumbing
	PlumbingStartCB m_pPlumbingStartCallback;

	CTexture* m_pTexture;

	CAnimator* m_pAnimatorCurrent;
	CAnimator* m_pAnimatorIdle;
	CAnimator* m_pAnimatorRunning;

	CVector2D m_Position;
	CVector2D m_Velocity;
	CVector2D m_Speed;
	CVector2D m_CollisionQuadOffset;

	uint32_t m_LookDirection;

	int32_t m_CurrentTriggerID;
	int32_t m_HorizontalDirection;
	int32_t m_VerticalDirection;

	bool m_Plumbing;

	SDL_FRect m_CollisionQuad;

};