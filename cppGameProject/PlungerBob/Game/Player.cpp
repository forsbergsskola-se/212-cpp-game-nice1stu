#include "Player.h"

#include "Framework/RenderDevice.h"
#include "Framework/TextureFactory.h"
#include "Framework/InputHandler.h"

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
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Create()
{
	const CVector2D FrameSize = CVector2D(128.0f, 128.0f);

	m_pTexture = CTextureFactory::GetInstance().CreateTexture("Plumber.png");
	m_pTexture->SetSize(FrameSize);
	m_pTexture->SetTextureCoords(0, FrameSize.x, 0, FrameSize.y);

	m_Position = CRenderDevice::GetInstance().GetWindow()->GetCenter() - (FrameSize * 0.5);
	m_Velocity = CVector2D(300.0f, 300.0f);

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

void CPlayer::Update(const float Deltatime)
{
	if (m_pPlayerAnimatorCurrent)
	{
		m_pPlayerAnimatorCurrent->Update(Deltatime);
	}

	const CVector2D MoveAmount = m_Speed * Deltatime;

	m_Position.x += MoveAmount.x;

	

	m_Position.y += MoveAmount.y;

}

void CPlayer::Render()
{
	CRenderDevice::GetInstance().RenderCopy(m_pTexture, m_Position);
}

void CPlayer::RenderDebug()
{

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
