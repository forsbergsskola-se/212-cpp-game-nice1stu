#include "Player.h"

#include "Framework/RenderDevice.h"
#include "Framework/TextureFactory.h"
#include "Framework/InputHandler.h"

CPlayer::CPlayer()
:m_pTexture (nullptr)
, m_Position(CVector2D::Zero)
, m_Velocity(CVector2D::Zero)
,m_Speed(CVector2D::Zero)

{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Create()
{
	const CVector2D FrameSize = CVector2D(128.0f, 128.0f);

	m_pTexture = CTextureFactory::GetInstance().CreateTexture("Plumber.png");
	m_pTexture->SetTextureCoords(0, FrameSize.x, 0, FrameSize.y);

	m_Position = CRenderDevice::GetInstance().GetWindow()->GetCenter() - (FrameSize * 0.5);
	m_Velocity = CVector2D(300.0f, 300.0f);

	return true;
}

void CPlayer::Destroy()
{
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
		m_Speed.x = -m_Velocity.x;
	}

	else if (rInputHandler.KeyHeld(SDL_SCANCODE_RIGHT) && !rInputHandler.KeyHeld(SDL_SCANCODE_LEFT))
	{
		m_Speed.x = m_Velocity.x;
	}
	
	if (rInputHandler.KeyHeld(SDL_SCANCODE_UP) && !rInputHandler.KeyHeld(SDL_SCANCODE_DOWN))
	{
		m_Speed.y = -m_Velocity.y;
	}

	else if (rInputHandler.KeyHeld(SDL_SCANCODE_DOWN) && !rInputHandler.KeyHeld(SDL_SCANCODE_UP))
	{
		m_Speed.y = m_Velocity.y;
	}

	/////////////////////////////////////////////////////

	//Released Keys
	if (rInputHandler.KeyReleased(SDL_SCANCODE_LEFT))
	{
		m_Speed.x = 0.0f;
	}

	else if (rInputHandler.KeyReleased(SDL_SCANCODE_RIGHT))
	{
		m_Speed.x = 0.0f;
	}

	if (rInputHandler.KeyReleased(SDL_SCANCODE_UP))
	{
		m_Speed.y = 0.0f;
	}

	else if (rInputHandler.KeyReleased(SDL_SCANCODE_DOWN))
	{
		m_Speed.y = 0.0f;
	}
}

void CPlayer::Update(const float Deltatime)
{
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