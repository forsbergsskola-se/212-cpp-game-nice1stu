#include "Game.h"

#include "Framework/InputHandler.h"
#include "Framework/TextureFactory.h"
#include "Framework/RenderDevice.h"
#include "Application.h"

CGame::CGame()
: m_pLevel(nullptr)
, m_pPlayer(nullptr)
, m_pStartScreenTexture(nullptr)
, m_State(EState::IDLE)
{
}

CGame::~CGame()
{
}

bool CGame::Create()
{
	m_pLevel = new CLevel;

	if (!m_pLevel->Create())
	{
		printf("Error: Failed to create level\n");

		return false;
	}

	m_pPlayer = new CPlayer;

	if (!m_pPlayer->Create())
	{
		printf("Error: Failed to create player\n");

		return false;
	}

	const CVector2D WindowCenter = CRenderDevice::GetInstance().GetWindow()->GetCenter();

	m_pStartScreenTexture = CTextureFactory::GetInstance().CreateTexture("Start screen.png");
	m_pStartScreenTexture->SetPosition(WindowCenter - m_pStartScreenTexture->GetSize() * 0.5f);

	return true;
}

void CGame::Destroy()
{
	CTextureFactory::GetInstance().DestroyTexture(m_pStartScreenTexture->GetName());

	m_pPlayer->Destroy();
	delete m_pPlayer;
	m_pPlayer = nullptr;

	m_pLevel->Destroy();
	delete m_pLevel;
	m_pLevel = nullptr;
}

void CGame::Update(const float Deltatime)
{
	CInputHandler& rInputHandler = CInputHandler::GetInstance();

	if (rInputHandler.KeyPressed(SDL_SCANCODE_ESCAPE))
	{
		CApplication::GetInstance().Quit();
	}
	//m_pPlayer->HandleInput();
	//m_pPlayer->Update(Deltatime);
	if (m_State == EState::IDLE)
	{
		if (CInputHandler::GetInstance().KeyPressed(SDL_SCANCODE_SPACE))
		{
			m_State = EState::COUNT_DOWN;
		}
	}
	else if (m_State == EState::COUNT_DOWN)
	{

	}
	else if (m_State == EState::PRE_START)
	{

	}
	else if (m_State == EState::ROUND_STARTED)
	{

	}
	else if (m_State == EState::ROUND_ENDED)
	{

	}
}

void CGame::Render()
{
	m_pLevel->Render();
	//m_pPlayer->Render();
	if (m_State == EState::IDLE)
	{
		CRenderDevice::GetInstance().RenderCopy(m_pStartScreenTexture);
	}
	else if (m_State == EState::COUNT_DOWN)
	{

	}
	else if (m_State == EState::PRE_START)
	{

	}
	else if (m_State == EState::ROUND_STARTED)
	{

	}
	else if (m_State == EState::ROUND_ENDED)
	{

	}
}

void CGame::RenderDebug()
{
	//m_pLevel->RenderDebug();
	m_pPlayer->RenderDebug();
}
