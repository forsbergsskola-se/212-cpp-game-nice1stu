#include "Player.h"

#include "Framework/InputHandler.h"
#include "Framework/RenderDevice.h"
#include "Framework/TextureHandler.h"

static bool QuadVsQuad(const SDL_FRect& rQuad1, const SDL_FRect& rQuad2, SDL_FRect* pIntersection = nullptr)
{
	SDL_FRect	Intersection = {0.0f, 0.0f, 0.0f, 0.0f};
	const bool	Result = (SDL_IntersectFRect(&rQuad1, &rQuad2, &Intersection) == SDL_TRUE);

	if(pIntersection)
	{
		pIntersection->x = Intersection.x;
		pIntersection->y = Intersection.y;
		pIntersection->w = Intersection.w;
		pIntersection->h = Intersection.h;
	}

	return Result;
}

CPlayer::CPlayer()
: m_pPlumbingStartCallback(nullptr)
, m_pTexture(nullptr)
, m_pAnimatorCurrent(nullptr)
, m_pAnimatorIdle(nullptr)
, m_pAnimatorRunning(nullptr)
, m_Position(CVector2D::Zero)
, m_Velocity(CVector2D::Zero)
, m_Speed(CVector2D::Zero)
, m_CollisionQuadOffset(CVector2D::Zero)
, m_LookDirection(1)
, m_CurrentTriggerID(-1)
, m_HorizontalDirection(EState::IDLE)
, m_VerticalDirection(EState::IDLE)
, m_Plumbing(false)
, m_CollisionQuad({0.0f, 0.0f, 0.0f, 0.0f})
{

}

CPlayer::~CPlayer()
{
}

bool CPlayer::Create()
{
	const CVector2D FrameSize = CVector2D(128.0f, 128.0f);
	const CVector2D PlayerSize = CVector2D(64.0f, 105.0f);

	m_pTexture = CTextureHandler::GetInstance().CreateTexture("Plumber.png");
	m_pTexture->SetSize(FrameSize);
	m_pTexture->SetTextureCoords(0, (uint32_t)FrameSize.x, 0, (uint32_t)FrameSize.y);

	//////////////////////////////////////////////////////////////////////////

	// Create animators that will be used more the player idle- and player running animation

	m_pAnimatorIdle		= new CAnimator;
	m_pAnimatorRunning	= new CAnimator;
	m_pAnimatorIdle->Set(m_pTexture,	9,	0, 8,	0, FrameSize, 15.0f, "PlumberIdle",		true, CAnimator::EDirection::FORWARD);
	m_pAnimatorRunning->Set(m_pTexture, 15, 0, 14,	1, FrameSize, 55.0f, "PlumberRunning",	true, CAnimator::EDirection::FORWARD);

	m_pAnimatorCurrent = m_pAnimatorIdle;

	//////////////////////////////////////////////////////////////////////////

	m_Position = CRenderDevice::GetInstance().GetWindow()->GetCenter() - (FrameSize * 0.5f);
	m_Velocity = CVector2D(300.0f, 300.0f);

	// An offset from each animation frame's upper left corner to where the player graphics starts, which is used for collision detection, together with the m_CollisionQuad below
	m_CollisionQuadOffset = CVector2D(35.0f, 10.0f);

	// Define the player collision quad that will be used to detect collision between the player and the walls, toilettes and toilette triggers
	m_CollisionQuad = {m_Position.x + m_CollisionQuadOffset.x, m_Position.y + m_CollisionQuadOffset.y, PlayerSize.x, PlayerSize.y};

	return true;
}

void CPlayer::Destroy()
{
	delete m_pAnimatorRunning;
	delete m_pAnimatorIdle;
	m_pAnimatorCurrent	= nullptr;
	m_pAnimatorIdle		= nullptr;
	m_pAnimatorRunning	= nullptr;

	CTextureHandler::GetInstance().DestroyTexture(m_pTexture->GetName());
}

void CPlayer::HandleInput()
{
	CInputHandler& rInputHandler = CInputHandler::GetInstance();

	// Pressed Keys

	if(rInputHandler.KeyPressed(SDL_SCANCODE_SPACE) && (m_CurrentTriggerID != -1) && !m_Plumbing)
	{
		m_Plumbing = true;

		m_pAnimatorCurrent = m_pAnimatorIdle;
		m_pAnimatorCurrent->Reset();

		if(m_pPlumbingStartCallback)
			m_pPlumbingStartCallback(m_CurrentTriggerID);

		return;
	}

	if(m_Plumbing)
		return;

	//////////////////////////////////////////////////////////////////////////

	//Held Keys

	if(rInputHandler.KeyHeld(SDL_SCANCODE_LEFT) && !rInputHandler.KeyHeld(SDL_SCANCODE_RIGHT))
	{
		m_LookDirection = 0;
		m_Speed.x = -m_Velocity.x;
		m_HorizontalDirection = RUNNING_LEFT;

		ActivateAnimation(m_pAnimatorRunning);
	}

	else if(rInputHandler.KeyHeld(SDL_SCANCODE_RIGHT) && !rInputHandler.KeyHeld(SDL_SCANCODE_LEFT))
	{
		m_LookDirection = 1;
		m_Speed.x = m_Velocity.x;
		m_HorizontalDirection = RUNNING_RIGHT;

		ActivateAnimation(m_pAnimatorRunning);
	}

	if(rInputHandler.KeyHeld(SDL_SCANCODE_UP) && !rInputHandler.KeyHeld(SDL_SCANCODE_DOWN))
	{
		m_Speed.y = -m_Velocity.y;
		m_VerticalDirection = RUNNING_UP;

		ActivateAnimation(m_pAnimatorRunning);
	}

	else if(rInputHandler.KeyHeld(SDL_SCANCODE_DOWN) && !rInputHandler.KeyHeld(SDL_SCANCODE_UP))
	{
		m_Speed.y = m_Velocity.y;
		m_VerticalDirection = RUNNING_DOWN;

		ActivateAnimation(m_pAnimatorRunning);
	}

	/////////////////////////////////////////////////////

	// Released Keys

	if(rInputHandler.KeyReleased(SDL_SCANCODE_LEFT) && (m_HorizontalDirection == RUNNING_LEFT))
	{
		m_Speed.x = 0.0f;
		m_HorizontalDirection = IDLE;

		if(m_VerticalDirection == IDLE)
			ActivateAnimation(m_pAnimatorIdle);
	}

	else if(rInputHandler.KeyReleased(SDL_SCANCODE_RIGHT) && (m_HorizontalDirection == RUNNING_RIGHT))
	{
		m_Speed.x = 0.0f;
		m_HorizontalDirection = IDLE;

		if(m_VerticalDirection == IDLE)
			ActivateAnimation(m_pAnimatorIdle);
	}

	if(rInputHandler.KeyReleased(SDL_SCANCODE_UP) && (m_VerticalDirection == RUNNING_UP))
	{
		m_Speed.y = 0.0f;
		m_VerticalDirection = IDLE;

		if(m_HorizontalDirection == IDLE)
			ActivateAnimation(m_pAnimatorIdle);
	}

	else if(rInputHandler.KeyReleased(SDL_SCANCODE_DOWN) && (m_VerticalDirection == RUNNING_DOWN))
	{
		m_Speed.y = 0.0f;
		m_VerticalDirection = IDLE;

		if(m_HorizontalDirection == IDLE)
			ActivateAnimation(m_pAnimatorIdle);
	}

	if((m_VerticalDirection == IDLE) && (m_HorizontalDirection == IDLE))
		ActivateAnimation(m_pAnimatorIdle);
}

void CPlayer::Update(const QuadVector& rCollisionQuads, const QuadVector& rToiletteQuads, const QuadVector& rTriggerQuads, const float Deltatime)
{
	if(m_pAnimatorCurrent)
		m_pAnimatorCurrent->Update(Deltatime);

	if(m_Plumbing)
		return;

	const CVector2D MoveAmount = m_Speed * Deltatime;

	if(m_HorizontalDirection != EState::IDLE)
	{
		m_Position.x += MoveAmount.x;

		m_CollisionQuad.x = m_Position.x + m_CollisionQuadOffset.x;

		for(const SDL_FRect& rCollisionQuad : rCollisionQuads)
		{
			ResolveXCollision(rCollisionQuad, MoveAmount);
		}

		for(const SDL_FRect& rCollisionQuad : rToiletteQuads)
		{
			ResolveXCollision(rCollisionQuad, MoveAmount);
		}
	}

	if(m_VerticalDirection != EState::IDLE)
	{
		m_Position.y += MoveAmount.y;

		m_CollisionQuad.y = m_Position.y + m_CollisionQuadOffset.y;

		for(const SDL_FRect& rCollisionQuad : rCollisionQuads)
		{
			ResolveYCollision(rCollisionQuad, MoveAmount);
		}

		for(const SDL_FRect& rCollisionQuad : rToiletteQuads)
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
	CRenderDevice& rRenderDevice = CRenderDevice::GetInstance();

	rRenderDevice.SetRenderDrawColor({0, 200, 0, 100});
	rRenderDevice.RenderQuad(m_CollisionQuad, true);
}

void CPlayer::PlumbingFinished()
{
	m_pAnimatorCurrent = m_pAnimatorIdle;
	m_pAnimatorCurrent->Reset();

	m_Plumbing = false;
}

void CPlayer::Reset()
{
	m_pAnimatorCurrent = m_pAnimatorIdle;
	m_pAnimatorCurrent->Reset();

	m_Speed = CVector2D::Zero;

	m_CurrentTriggerID = -1;

	m_HorizontalDirection	= EState::IDLE;
	m_VerticalDirection		= EState::IDLE;

	m_Plumbing = false;
}

void CPlayer::CheckTriggers(const QuadVector& rTriggerQuads)
{
	if(m_CurrentTriggerID != -1)
	{
		if(!QuadVsQuad(m_CollisionQuad, rTriggerQuads[m_CurrentTriggerID]))
			m_CurrentTriggerID = -1;
	}

	else
	{
		for(uint32_t i = 0; i < rTriggerQuads.size(); ++i)
		{
			if(QuadVsQuad(m_CollisionQuad, rTriggerQuads[i]))
			{
				m_CurrentTriggerID = i;

				break;
			}
		}
	}
}

void CPlayer::ResolveXCollision(const SDL_FRect& rLevelCollisionQuad, const CVector2D& rMoveAmount)
{
	// The player is moving to the left
	if(rMoveAmount.x < 0.0f)
	{
		SDL_FRect Intersection = {0.0f, 0.0f, 0.0f, 0.0f};

		if(QuadVsQuad(m_CollisionQuad, rLevelCollisionQuad, &Intersection))
		{
			m_Position.x += Intersection.w;

			m_CollisionQuad.x = m_Position.x + m_CollisionQuadOffset.x;

			m_Speed.x = 0.0f;
		}
	}

	// The player is moving to the right
	else if(rMoveAmount.x > 0.0f)
	{
		SDL_FRect Intersection = {0.0f, 0.0f, 0.0f, 0.0f};

		if(QuadVsQuad(m_CollisionQuad, rLevelCollisionQuad, &Intersection))
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
	if(rMoveAmount.y < 0.0f)
	{
		SDL_FRect Intersection = {0.0f, 0.0f, 0.0f, 0.0f};

		if(QuadVsQuad(m_CollisionQuad, rLevelCollisionQuad, &Intersection))
		{
			m_Position.y += Intersection.h;

			m_CollisionQuad.y = m_Position.y + m_CollisionQuadOffset.y;

			m_Speed.y = 0.0f;
		}
	}

	// The player is moving down
	else if(rMoveAmount.y > 0.0f)
	{
		SDL_FRect Intersection = {0.0f, 0.0f, 0.0f, 0.0f};

		if(QuadVsQuad(m_CollisionQuad, rLevelCollisionQuad, &Intersection))
		{
			m_Position.y -= Intersection.h;

			m_CollisionQuad.y = m_Position.y + m_CollisionQuadOffset.y;

			m_Speed.y = 0.0f;
		}
	}
}

void CPlayer::ActivateAnimation(CAnimator* pAnimator)
{
	if(m_pAnimatorCurrent && (m_pAnimatorCurrent != pAnimator))
	{
		m_pAnimatorCurrent = pAnimator;
		m_pAnimatorCurrent->Reset();
	}

	const bool Flipped = (m_LookDirection == 0);

	m_pTexture->SetFlipMethod(Flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}