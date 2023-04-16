#include "Game.h"

#include "Application.h"
#include "Framework/InputHandler.h"
#include "Framework/RenderDevice.h"
#include "Framework/TextureHandler.h"

CGame::CGame()
: m_pLevel(nullptr)
, m_pPlayer(nullptr)
, m_pStartScreenTexture(nullptr)
, m_pCountdownTexture(nullptr)
, m_pGoTexture(nullptr)
, m_pWaterTexture(nullptr)
, m_pPlungerTexture(nullptr)
, m_pEndScreenTexture(nullptr)
, m_pCountdownAnimator(nullptr)
, m_pPlumbingAnimator(nullptr)
, m_CountdownTimerDefault(3.0f)
, m_CountdownTimer(m_CountdownTimerDefault)
, m_PreStartTimerDefault(1.0f)
, m_PreStartTimer(m_PreStartTimerDefault)
, m_ActivationTimerDefault(3.0f)
, m_ActivationTimer(0.0f)
, m_PlumbingTimerDefault(2.0f)
, m_PlumbingTimer(m_PlumbingTimerDefault)
, m_EndScreenTimerDefault(4.0f)
, m_EndScreenTimer(m_EndScreenTimerDefault)
, m_CurrentToilet(0)
, m_NumActivatedToilets(0)
, m_PlumbingStarted(false)
, m_State(EState::IDLE)
{

}

CGame::~CGame()
{
}

bool CGame::Create()
{
	m_pLevel = new CLevel;

	if(!m_pLevel->Create())
	{
		printf("Error: Failed to create level\n");

		return false;
	}

	m_pPlayer = new CPlayer;

	if(!m_pPlayer->Create())
	{
		printf("Error: Failed to create player\n");

		return false;
	}

	m_pPlayer->SetPlumbingStartCallback(std::bind(&CGame::OnPlumbingStart, this, std::placeholders::_1));

	//////////////////////////////////////////////////////////////////////////

	// Create textures

	CTextureHandler&	rTextureHandler		= CTextureHandler::GetInstance();
	const CWindow*		pWindow				= CRenderDevice::GetInstance().GetWindow();
	const CVector2D		WindowCenter		= pWindow->GetCenter();
	const CVector2D		CountdownFrameSize	= CVector2D(164.0f, 228.0f);
	const CVector2D		WaterFrameSize		= CVector2D(65.0f, 106.0f);
	const CVector2D		PlungerFrameSize	= CVector2D(200.0f, 112.0f);

	m_pStartScreenTexture	= rTextureHandler.CreateTexture("Start screen.png");
	m_pCountdownTexture		= rTextureHandler.CreateTexture("Countdown.png");
	m_pGoTexture			= rTextureHandler.CreateTexture("Go.png");
	m_pWaterTexture			= rTextureHandler.CreateTexture("Water.png");
	m_pPlungerTexture		= rTextureHandler.CreateTexture("Plunger.png");
	m_pEndScreenTexture		= rTextureHandler.CreateTexture("End screen.png");

	m_pStartScreenTexture->SetPosition(WindowCenter - m_pStartScreenTexture->GetSize() * 0.5f);

	m_pCountdownTexture->SetSize(CountdownFrameSize);
	m_pCountdownTexture->SetPosition(WindowCenter - m_pCountdownTexture->GetSize() * 0.5f);
	m_pCountdownTexture->SetTextureCoords((uint32_t)(CountdownFrameSize.x * m_CountdownTimer), (uint32_t)((CountdownFrameSize.x * m_CountdownTimer) + CountdownFrameSize.x), 0, (uint32_t)CountdownFrameSize.y);

	m_pGoTexture->SetPosition(WindowCenter - m_pGoTexture->GetSize() * 0.5f);

	m_pWaterTexture->SetSize(WaterFrameSize);

	m_pPlungerTexture->SetSize(PlungerFrameSize * 3.0f);
	m_pPlungerTexture->SetTextureCoords(0, (uint32_t)PlungerFrameSize.x, 0, (uint32_t)PlungerFrameSize.y);
	m_pPlungerTexture->SetPosition(WindowCenter - (m_pPlungerTexture->GetSize() * 0.5f));

	m_pEndScreenTexture->SetSize(pWindow->GetSize());
	m_pEndScreenTexture->SetPosition(WindowCenter - (m_pEndScreenTexture->GetSize() * 0.5f));

	//////////////////////////////////////////////////////////////////////////

	// Create the animators that will animate the countdown texture and the plumbing texture

	m_pCountdownAnimator = new CAnimator;
	m_pCountdownAnimator->Set(m_pCountdownTexture, 10, (uint32_t)m_CountdownTimerDefault, 0, 0, CountdownFrameSize, 1.0f, "Countdown", false, CAnimator::EDirection::BACKWARD);

	m_pPlumbingAnimator	= new CAnimator;
	m_pPlumbingAnimator->Set(m_pPlungerTexture, 10, 0, 9, 0, PlungerFrameSize, 8.0f, "Plumbing", true, CAnimator::EDirection::FORWARD);

	//////////////////////////////////////////////////////////////////////////

	// Create the toilets

	const CLevel::QuadVector& rToiletQuads = m_pLevel->GetToiletQuads();

	uint32_t Index = 0;

	for(const SDL_FRect& rToiletQuad : rToiletQuads)
	{
		CToilet* pToilet = new CToilet;
		pToilet->Create(CVector2D(rToiletQuad.x, rToiletQuad.y), WaterFrameSize, (Index < (rToiletQuads.size() / 2)));

		m_Toilets.push_back(pToilet);

		++Index;
	}

	//////////////////////////////////////////////////////////////////////////

	m_RandomNumberGenerator.Seed();

	return true;
}

void CGame::Destroy()
{
	for(CToilet* pToilet : m_Toilets)
	{
		delete pToilet;
	}

	m_Toilets.clear();

	delete m_pCountdownAnimator;
	m_pCountdownAnimator = nullptr;

	CTextureHandler& rTextureHandler = CTextureHandler::GetInstance();

	rTextureHandler.DestroyTexture(m_pEndScreenTexture->GetName());
	rTextureHandler.DestroyTexture(m_pPlungerTexture->GetName());
	rTextureHandler.DestroyTexture(m_pWaterTexture->GetName());
	rTextureHandler.DestroyTexture(m_pGoTexture->GetName());
	rTextureHandler.DestroyTexture(m_pCountdownTexture->GetName());
	rTextureHandler.DestroyTexture(m_pStartScreenTexture->GetName());
	m_pEndScreenTexture		= nullptr;
	m_pPlungerTexture		= nullptr;
	m_pWaterTexture			= nullptr;
	m_pGoTexture			= nullptr;
	m_pCountdownTexture		= nullptr;
	m_pStartScreenTexture	= nullptr;

	m_pPlayer->Destroy();
	delete m_pPlayer;
	m_pPlayer = nullptr;

	m_pLevel->Destroy();
	delete m_pLevel;
	m_pLevel = nullptr;
}

void CGame::Update(const float Deltatime)
{
	if(CInputHandler::GetInstance().KeyPressed(SDL_SCANCODE_ESCAPE))
		CApplication::GetInstance().Quit();

	if(m_State == EState::IDLE)
	{
		if(CInputHandler::GetInstance().KeyPressed(SDL_SCANCODE_SPACE))
			m_State = EState::COUNT_DOWN;
	}

	else if(m_State == EState::COUNT_DOWN)
	{
		m_pCountdownAnimator->Update(Deltatime);

		if(m_pCountdownAnimator->GetCurrentFrame() == m_pCountdownAnimator->GetEndFrame())
		{
			m_pCountdownAnimator->Reset();

			m_State = EState::PRE_START;
		}
	}

	else if(m_State == EState::PRE_START)
	{
		m_PreStartTimer -= Deltatime;

		if(m_PreStartTimer <= 0.0f)
		{
			m_State = EState::ROUND_STARTED;

			Reset();
		}
	}

	else if(m_State == EState::ROUND_STARTED)
	{
		m_pPlayer->HandleInput();
		m_pPlayer->Update(m_pLevel->GetCollisionQuads(), m_pLevel->GetToiletQuads(), m_pLevel->GetTriggerQuads(), Deltatime);

		m_ActivationTimer -= Deltatime;

		if(m_ActivationTimer <= 0.0f)
		{
			m_ActivationTimer = m_ActivationTimerDefault;

			ActivateRandomToilet();

			m_pPlumbingAnimator->Reset();
		}

		for(CToilet* pToilet : m_Toilets)
		{
			pToilet->Update(Deltatime);
		}	

		if(m_PlumbingStarted)
		{
			m_PlumbingTimer -= Deltatime;

			if(m_PlumbingTimer <= 0.0f)
			{
				m_pPlayer->PlumbingFinished();

				m_Toilets[m_CurrentToilet]->Reset();

				m_PlumbingTimer = 0.0f;

				if(m_NumActivatedToilets > 0)
					m_NumActivatedToilets--;

				m_PlumbingStarted = false;
			}

			m_pPlumbingAnimator->Update(Deltatime);
		}
	}

	else if(m_State == EState::ROUND_ENDED)
	{
		m_EndScreenTimer -= Deltatime;

		if(m_EndScreenTimer <= 0.0f)
		{
			m_EndScreenTimer = m_EndScreenTimerDefault;

			m_State = EState::IDLE;
		}
	}
}

void CGame::Render()
{
	m_pLevel->Render();

	if(m_State == EState::IDLE)
		CRenderDevice::GetInstance().RenderCopy(m_pStartScreenTexture);

	else if(m_State == EState::COUNT_DOWN)
		CRenderDevice::GetInstance().RenderCopy(m_pCountdownTexture);

	else if(m_State == EState::PRE_START)
		CRenderDevice::GetInstance().RenderCopy(m_pGoTexture);

	else if(m_State == EState::ROUND_STARTED)
	{
		for(CToilet* pToilet : m_Toilets)
		{
			pToilet->Render(m_pWaterTexture);
		}

		m_pPlayer->Render();

		// When there's 6 or more toilets that are full, flash a red transparent quad over the whole screen 
		if(m_NumActivatedToilets >= m_Toilets.size() - 2)
		{
			CRenderDevice& rRenderDevice = CRenderDevice::GetInstance();

			const CVector2D	WindowSize		= rRenderDevice.GetWindow()->GetSize();
			const float		Sinus			= (sinf((float)CApplication::GetInstance().GetTimer()->GetLifeTime() * 8.0f) + 1.0f) * 0.5f;
			const SDL_Color FlashingColor	= {200, 0, 0, (Uint8)(80.0f * Sinus)};
			const SDL_FRect	FlashingQuad	= {0.0f, 0.0f, WindowSize.x, WindowSize.y};

			rRenderDevice.SetRenderDrawColor(FlashingColor);
			rRenderDevice.RenderQuad(FlashingQuad, true);
		}

		if(m_PlumbingStarted)
			CRenderDevice::GetInstance().RenderCopy(m_pPlungerTexture);
	}

	else if(m_State == EState::ROUND_ENDED)
		CRenderDevice::GetInstance().RenderCopy(m_pEndScreenTexture);
}

void CGame::RenderDebug()
{
	if(m_State == EState::ROUND_STARTED)
	{
	//	m_pLevel->RenderDebug();

		for(CToilet* pToilet : m_Toilets)
		{
		//	pToilet->RenderDebug();
		}

	//	m_pPlayer->RenderDebug();
	}
}

void CGame::Reset()
{
	m_RandomNumberGenerator.Seed();

	m_ActivationTimer = 0.0f;

	m_CurrentToilet		= 0;
	m_NumActivatedToilets = 0;

	m_PlumbingStarted = false;

	m_pPlayer->Reset();

	for(CToilet* pToilet : m_Toilets)
	{
		pToilet->Reset();
	}
}

void CGame::ActivateRandomToilet()
{
	const uint32_t	NumToilets	= (uint32_t)m_Toilets.size();
	uint32_t		Index			= m_RandomNumberGenerator.RandomUint(0, NumToilets - 1);

	m_NumActivatedToilets = 0;

	for(CToilet* pToilet : m_Toilets)
	{
		if(pToilet->GetActivated())
			m_NumActivatedToilets++;
	}

	if(m_NumActivatedToilets < NumToilets)
	{
		while(m_Toilets[Index]->GetActivated())
		{
			Index = m_RandomNumberGenerator.RandomUint(0, NumToilets - 1);
		}

		m_Toilets[Index]->Activate();
	}

	else
		m_State = EState::ROUND_ENDED;
}

void CGame::OnPlumbingStart(const uint32_t ToiletteID)
{
	m_PlumbingTimer = m_PlumbingTimerDefault;

	m_CurrentToilet = ToiletteID;

	m_PlumbingStarted = true;
}