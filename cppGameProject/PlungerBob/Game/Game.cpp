#include "Game.h"

#include "Framework/InputHandler.h"
#include "Framework/TextureFactory.h"
#include "Framework/RenderDevice.h"
#include "Application.h"

CGame::CGame()
	: m_pLevel(nullptr)
	, m_pPlayer(nullptr)
	, m_pStartScreenTexture(nullptr)
	, m_pCountdownTexture(nullptr)
	, m_pGoTexture(nullptr)
	, m_pCountdownAnimator(nullptr)
	, m_CountdownTimerDefault(3.0f)
	, m_CountdownTimer(m_CountdownTimerDefault)
	, m_GameStartTimer(1.0f)
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

	CTextureFactory& rTextureFactory = CTextureFactory::GetInstance();

	const CVector2D WindowCenter = CRenderDevice::GetInstance().GetWindow()->GetCenter();
	const CVector2D CountdownFrameSize = CVector2D(164.0f, 228.0f);


	m_pStartScreenTexture = rTextureFactory.CreateTexture("Start screen.png");
	m_pCountdownTexture = rTextureFactory.CreateTexture("Countdown.png");
	m_pGoTexture = rTextureFactory.CreateTexture("Go.png");

	m_pStartScreenTexture->SetPosition(WindowCenter - m_pStartScreenTexture->GetSize() * 0.5f);

	m_pCountdownTexture->SetSize(CountdownFrameSize);
	m_pCountdownTexture->SetPosition(WindowCenter - m_pCountdownTexture->GetSize() * 0.5f);
	m_pCountdownTexture->SetTextureCoords(CountdownFrameSize.x * m_CountdownTimer, (CountdownFrameSize.x * m_CountdownTimer) + CountdownFrameSize.x, 0, CountdownFrameSize.y);

	m_pGoTexture->SetPosition(WindowCenter - m_pGoTexture->GetSize() * 0.5f);

	m_pCountdownAnimator = new CAnimator;
	m_pCountdownAnimator->Set(m_pCountdownTexture, 10, m_CountdownTimerDefault, 0, 0, CountdownFrameSize, 1.0f, "Countdown", false, CAnimator::EDirection::BACKWARD);

	return true;
}

void CGame::Destroy()
{
	delete m_pCountdownAnimator;
	m_pCountdownAnimator = nullptr;

	CTextureFactory& rTextureFactory = CTextureFactory::GetInstance();

	rTextureFactory.DestroyTexture(m_pGoTexture->GetName());
	rTextureFactory.DestroyTexture(m_pCountdownTexture->GetName());
	rTextureFactory.DestroyTexture(m_pStartScreenTexture->GetName());

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

	if (m_State == EState::IDLE)
	{
		if (CInputHandler::GetInstance().KeyPressed(SDL_SCANCODE_SPACE))
		{
			m_State = EState::COUNT_DOWN;
		}
	}
	else if (m_State == EState::COUNT_DOWN)
	{
		m_pCountdownAnimator->Update(Deltatime);

		if (m_pCountdownAnimator->GetCurrentFrame() == m_pCountdownAnimator->GetEndFrame())
		{
			m_pCountdownAnimator->Reset();

			m_State = EState::PRE_START;
		}
	}
	else if (m_State == EState::PRE_START)
	{
		m_GameStartTimer -= Deltatime;

		if (m_GameStartTimer <= 0)
		{
			m_State = EState::ROUND_STARTED;
		}
	}
	else if (m_State == EState::ROUND_STARTED)
	{
		m_pPlayer->HandleInput();
		m_pPlayer->Update(Deltatime);
	}
	else if (m_State == EState::ROUND_ENDED)
	{

	}
}

void CGame::Render()
{
	m_pLevel->Render();

	if (m_State == EState::IDLE)
	{
		CRenderDevice::GetInstance().RenderCopy(m_pStartScreenTexture);
	}
	else if (m_State == EState::COUNT_DOWN)
	{
		CRenderDevice::GetInstance().RenderCopy(m_pCountdownTexture);
	}
	else if (m_State == EState::PRE_START)
	{
		CRenderDevice::GetInstance().RenderCopy(m_pGoTexture);
	}
	else if (m_State == EState::ROUND_STARTED)
	{
		m_pPlayer->Render();
	}
	else if (m_State == EState::ROUND_ENDED)
	{

	}
}

void CGame::RenderDebug()
{
	if (m_State == EState::ROUND_STARTED)
	{
		m_pLevel->RenderDebug();
		m_pPlayer->RenderDebug();
	}
}
