#include "Player.h"

#include "Framework/RenderDevice.h"
#include "Framework/TextureFactory.h"
#include "Framework/InputHandler.h"

static bool QuadVsQuad(const SDL_FRect& rQuad1, const SDL_FRect& rQuad2, SDL_FRect* pIntersection = nullptr)
{
	SDL_FRect	Intersection = { 0.0f, 0.0f, 0.0f, 0.0f };
	const bool	Result = (SDL_IntersectFRect(&rQuad1, &rQuad2, &Intersection) == SDL_TRUE);

	if (pIntersection)
	{
		pIntersection->x = Intersection.x;
		pIntersection->y = Intersection.y;
		pIntersection->w = Intersection.w;
		pIntersection->h = Intersection.h;
	}

	return Result;
}

CPlayer::CPlayer()
:m_pTexture (nullptr)
, m_Position(CVector2D::Zero)
, m_Velocity(CVector2D::Zero)
, m_Speed(CVector2D::Zero)
, m_pPlayerAnimatorCurrent(nullptr)
, m_pPlayerAnimatorIdle(nullptr)
, m_pPlayerAnimatorRunning(nullptr)
, m_HorizontalDirection(EPLayerState::IDLE)
, m_VerticalDirection(EPLayerState::IDLE)
, m_LookDirection(1)
, m_CollisionQuad({ 0.0f, 0.0f, 0.0f, 0.0f })
, m_CollisionQuadOffset(CVector2D::Zero)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Create()
{
	const CVector2D FrameSize = CVector2D(128.0f, 128.0f);
	const CVector2D PlayerSize = CVector2D(64.0f, 105.0f);
	

	m_pTexture = CTextureFactory::GetInstance().CreateTexture("Plumber.png");
	m_pTexture->SetSize(FrameSize);

	m_pTexture->SetTextureCoords(0, FrameSize.x, 0, FrameSize.y);

	m_Position = CRenderDevice::GetInstance().GetWindow()->GetCenter() - (FrameSize * 0.5);
	m_Velocity = CVector2D(300.0f, 300.0f);
	m_CollisionQuadOffset = CVector2D(35.0f, 10.0f);
	m_CollisionQuad = { m_Position.x + m_CollisionQuadOffset.x, m_Position.y + m_CollisionQuadOffset.y, PlayerSize.x, PlayerSize.y };

	m_pPlayerAnimatorIdle = new CAnimator;
	m_pPlayerAnimatorRunning = new CAnimator;
	m_pPlayerAnimatorIdle->Set(m_pTexture, 9, 0, 8, 0, FrameSize, 15.0f, "PlumberIdle", true, CAnimator::EDirection::FORWARD);
	m_pPlayerAnimatorRunning->Set(m_pTexture, 15, 0, 14, 1, FrameSize, 55.0f, "PlumberRunning", true, CAnimator::EDirection::FORWARD);
	m_pPlayerAnimatorCurrent = m_pPlayerAnimatorIdle;


	return true;
}

void CPlayer::Destroy()
{
	delete m_pPlayerAnimatorRunning;
	m_pPlayerAnimatorRunning = nullptr;

	delete m_pPlayerAnimatorIdle;
	m_pPlayerAnimatorIdle = nullptr;


	CTextureFactory::GetInstance().DestroyTexture(m_pTexture->GetName());
}

void CPlayer::HandleInput()
{
	CInputHandler& rInputHandler = CInputHandler::GetInstance();

	// Pressed Keys



	/////////////////////////////////////////////////////

	//Held Keys
	if (rInputHandler.KeyHeld(SDL_SCANCODE_LEFT) && !rInputHandler.KeyHeld(SDL_SCANCODE_RIGHT))
	{
		m_LookDirection = 0;
		m_Speed.x = -m_Velocity.x;
		m_HorizontalDirection = RUNNING_LEFT;
		ActivateRunningAnimation();
	}

	else if (rInputHandler.KeyHeld(SDL_SCANCODE_RIGHT) && !rInputHandler.KeyHeld(SDL_SCANCODE_LEFT))
	{
		m_LookDirection = 1;
		m_Speed.x = m_Velocity.x;
		m_HorizontalDirection = RUNNING_RIGHT;
		ActivateRunningAnimation();
	}
	
	if (rInputHandler.KeyHeld(SDL_SCANCODE_UP) && !rInputHandler.KeyHeld(SDL_SCANCODE_DOWN))
	{
		m_Speed.y = -m_Velocity.y;
		m_VerticalDirection = RUNNING_UP;
		ActivateRunningAnimation();
	}

	else if (rInputHandler.KeyHeld(SDL_SCANCODE_DOWN) && !rInputHandler.KeyHeld(SDL_SCANCODE_UP))
	{
		m_Speed.y = m_Velocity.y;
		m_VerticalDirection = RUNNING_DOWN;
		ActivateRunningAnimation();
	}

	/////////////////////////////////////////////////////

	//Released Keys
	if (rInputHandler.KeyReleased(SDL_SCANCODE_LEFT) && m_HorizontalDirection == RUNNING_LEFT)
	{
		m_Speed.x = 0.0f;
		m_HorizontalDirection = IDLE;
		if (m_VerticalDirection == IDLE)
		{
			ActivateIdleAnimation();
		}
	}

	else if (rInputHandler.KeyReleased(SDL_SCANCODE_RIGHT) && m_HorizontalDirection == RUNNING_RIGHT)
	{
		m_Speed.x = 0.0f;
		m_HorizontalDirection = IDLE;
		if (m_VerticalDirection == IDLE)
		{
			ActivateIdleAnimation();
		}
	}

	if (rInputHandler.KeyReleased(SDL_SCANCODE_UP) && m_VerticalDirection == RUNNING_UP)
	{
		m_Speed.y = 0.0f;
		m_VerticalDirection = IDLE;
		if (m_HorizontalDirection == IDLE)
		{
			ActivateIdleAnimation();
		}
	}

	else if (rInputHandler.KeyReleased(SDL_SCANCODE_DOWN) && m_VerticalDirection == RUNNING_DOWN)
	{
		m_Speed.y = 0.0f;
		m_VerticalDirection = IDLE;		
		if (m_HorizontalDirection == IDLE)
		{
			ActivateIdleAnimation();
		}
	}

	if (m_VerticalDirection == IDLE && m_HorizontalDirection == IDLE)
	{
		ActivateIdleAnimation();
	}
}

void CPlayer::Update(const QuadVector& rCollisionQuads, const QuadVector& rToiletteQuads, const QuadVector& rTriggerQuads, const float Deltatime)
{
	if (m_pPlayerAnimatorCurrent)
	{
		m_pPlayerAnimatorCurrent->Update(Deltatime);
	}

	if (m_Plumbing)
	{
		return;
	}
	const CVector2D MoveAmount = m_Speed * Deltatime;

	if (m_HorizontalDirection != IDLE)
	{
		m_Position.x += MoveAmount.x;

		m_CollisionQuad.x = m_Position.x + m_CollisionQuadOffset.x;

		for (const SDL_FRect& rCollisionQuad : rCollisionQuads)
		{
			ResolveYCollision(rCollisionQuad, MoveAmount);
		}

		for (const SDL_FRect& rCollisionQuad : rToiletteQuads)
		{
			ResolveXCollision(rCollisionQuad, MoveAmount);
		}
	}

	if (m_VerticalDirection != IDLE)
	{
		m_Position.y += MoveAmount.y;

		m_CollisionQuad.y = m_Position.y + m_CollisionQuadOffset.y;

		for (const SDL_FRect& rCollisionQuad : rCollisionQuads)
		{
			ResolveYCollision(rCollisionQuad, MoveAmount);
		}

		for (const SDL_FRect& rCollisionQuad : rToiletteQuads)
		{
			ResolveYCollision(rCollisionQuad, MoveAmount);
		}
	}

	CheckTriggers(rTriggerQuads);
}

void CPlayer::Render()
{
	CRenderDevice::GetInstance().RenderCopy(m_pTexture, m_Position);
}

void CPlayer::RenderDebug()
{

}

void CPlayer::PlumbingFinished()
{
	m_pPlayerAnimatorCurrent = m_pPlayerAnimatorIdle;
	m_pPlayerAnimatorCurrent->Reset();

	m_Plumbing = false;
}

void CPlayer::ActivateIdleAnimation()
{
	if (m_pPlayerAnimatorCurrent && (m_pPlayerAnimatorCurrent != m_pPlayerAnimatorIdle))
	{
		m_pPlayerAnimatorCurrent = m_pPlayerAnimatorIdle;
		m_pPlayerAnimatorCurrent->Reset();
	}
	const bool Flipped = (m_LookDirection == 0);
	m_pTexture->SetFlipMethod(Flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void CPlayer::ActivateRunningAnimation()
{
	if (m_pPlayerAnimatorCurrent && (m_pPlayerAnimatorCurrent != m_pPlayerAnimatorRunning))
	{
		m_pPlayerAnimatorCurrent = m_pPlayerAnimatorRunning;
		m_pPlayerAnimatorCurrent->Reset();
	}
	const bool Flipped = (m_LookDirection == 0);
	m_pTexture->SetFlipMethod(Flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void CPlayer::CheckTriggers(const QuadVector& rTriggerQuads)
{
	if (m_CurrentTRiggerID != 1)
	{
		if (!QuadVsQuad(m_CollisionQuad, rTriggerQuads[m_CurrentTRiggerID]))
			m_CurrentTRiggerID = -1;
	}
	else
	{
		for (int i = 0; i < rTriggerQuads.size(); ++i)
		{
			if (QuadVsQuad(m_CollisionQuad, rTriggerQuads[i]))
			{
				m_CurrentTRiggerID = i;

				break;
			}
		}
	}
}

void CPlayer::ResolveXCollision(const SDL_FRect& rLevelCollisionQuad, const CVector2D& rMoveAmount)
{
	// The player is moving to the left
	if (rMoveAmount.x < 0.0f)
	{
		SDL_FRect Intersection = { 0.0f, 0.0f, 0.0f, 0.0f };

		if (QuadVsQuad(m_CollisionQuad, rLevelCollisionQuad, &Intersection))
		{
			m_Position.x += Intersection.w;

			m_CollisionQuad.x = m_Position.x + m_CollisionQuadOffset.x;

			m_Speed.x = 0.0f;
		}
	}

	// The player is moving to the right
	else if (rMoveAmount.x > 0.0f)
	{
		SDL_FRect Intersection = { 0.0f, 0.0f, 0.0f, 0.0f };

		if (QuadVsQuad(m_CollisionQuad, rLevelCollisionQuad, &Intersection))
		{
			m_Position.x -= Intersection.w;

			m_CollisionQuad.x = m_Position.x + m_CollisionQuadOffset.x;

			m_Speed.x = 0.0f;
		}
	}
}

void CPlayer::ResolveYCollision(const SDL_FRect& rLevelCollisionQuad, const CVector2D& rMoveAmount)
{
	// The player is moving up
	if (rMoveAmount.y < 0.0f)
	{
		SDL_FRect Intersection = { 0.0f, 0.0f, 0.0f, 0.0f };

		if (QuadVsQuad(m_CollisionQuad, rLevelCollisionQuad, &Intersection))
		{
			m_Position.y += Intersection.h;

			m_CollisionQuad.y = m_Position.y + m_CollisionQuadOffset.y;

			m_Speed.y = 0.0f;
		}
	}

	// The player is moving down
	else if (rMoveAmount.y > 0.0f)
	{
		SDL_FRect Intersection = { 0.0f, 0.0f, 0.0f, 0.0f };

		if (QuadVsQuad(m_CollisionQuad, rLevelCollisionQuad, &Intersection))
		{
			m_Position.y -= Intersection.h;

			m_CollisionQuad.y = m_Position.y + m_CollisionQuadOffset.y;

			m_Speed.y = 0.0f;
		}
	}
}