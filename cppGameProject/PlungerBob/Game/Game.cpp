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
, m_pWaterTexture(nullptr)
, m_pPlungerTexture(nullptr)
, m_pEndScreenTexture(nullptr)
, m_pCountdownAnimator(nullptr)
, m_pPlumbingAnimator(nullptr)
, m_CountdownTimerDefault(3.0f)
, m_CountdownTimer(m_CountdownTimerDefault)
, m_PreStartTimerDefault(1.0f)
, m_PreStartTimer(m_PreStartTimerDefault)
, m_ActivationTimerDefault(7.0f)
, m_ActivationTimer(0.0f)
, m_PlumbingTimerDefault(2.0f)
, m_PlumbingTimer(m_PlumbingTimerDefault)
, m_EndScreenTimerDefault(4.0f)
, m_EndScreenTimer(m_EndScreenTimerDefault)
, m_CurrentToilette(0)
, m_NumActivatedToilettes(0)
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

	CTextureFactory&	rTextureFactory		= CTextureFactory::GetInstance();
	const CWindow*		pWindow				= CRenderDevice::GetInstance().GetWindow();
	const CVector2D		WindowCenter		= pWindow->GetCenter();
	const CVector2D		CountdownFrameSize	= CVector2D(164.0f, 228.0f);
	const CVector2D		WaterFrameSize		= CVector2D(65.0f, 106.0f);
	const CVector2D		PlungerFrameSize	= CVector2D(200.0f, 112.0f);

	m_pStartScreenTexture	= rTextureFactory.CreateTexture("Start screen.png");
	m_pCountdownTexture		= rTextureFactory.CreateTexture("Countdown.png");
	m_pGoTexture			= rTextureFactory.CreateTexture("Go.png");
	m_pWaterTexture			= rTextureFactory.CreateTexture("Water.png");
	m_pPlungerTexture		= rTextureFactory.CreateTexture("Plunger.png");
	m_pEndScreenTexture		= rTextureFactory.CreateTexture("End screen.png");

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

	// Create the toilettes

	const CLevel::QuadVector& rToiletteQuads = m_pLevel->GetToiletteQuads();

	for(uint32_t i = 0; i < rToiletteQuads.size(); ++i)
	{
		const SDL_FRect ToiletteQuad = rToiletteQuads[i];

		CToilette* pToilette = new CToilette;
		pToilette->Create(CVector2D(ToiletteQuad.x, ToiletteQuad.y), WaterFrameSize, (i < (rToiletteQuads.size() / 2)));

		m_Toilettes.push_back(pToilette);
	}

	//////////////////////////////////////////////////////////////////////////

	m_RandomNumberGenerator.Seed();

	return true;
}

void CGame::Destroy()
{
	for(CToilette* pToilette : m_Toilettes)
	{
		delete pToilette;
	}

	m_Toilettes.clear();

	delete m_pCountdownAnimator;
	m_pCountdownAnimator = nullptr;

	CTextureFactory& rTextureFactory = CTextureFactory::GetInstance();

	rTextureFactory.DestroyTexture(m_pEndScreenTexture->GetName());
	rTextureFactory.DestroyTexture(m_pPlungerTexture->GetName());
	rTextureFactory.DestroyTexture(m_pWaterTexture->GetName());
	rTextureFactory.DestroyTexture(m_pGoTexture->GetName());
	rTextureFactory.DestroyTexture(m_pCountdownTexture->GetName());
	rTextureFactory.DestroyTexture(m_pStartScreenTexture->GetName());
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
			m_State = EState::ROUND_STARTED;
	}

	else if(m_State == EState::ROUND_STARTED)
	{
		m_pPlayer->HandleInput();
		m_pPlayer->Update(m_pLevel->GetCollisionQuads(), m_pLevel->GetToiletteQuads(), m_pLevel->GetTriggerQuads(), Deltatime);

		m_ActivationTimer -= Deltatime;

		if(m_ActivationTimer <= 0.0f)
		{
			m_ActivationTimer = m_ActivationTimerDefault;

			ActivateRandomToilette();

			m_pPlumbingAnimator->Reset();
		}

		for(CToilette* pToilette : m_Toilettes)
		{
			pToilette->Update(Deltatime);
		}	

		if(m_PlumbingStarted)
		{
			m_PlumbingTimer -= Deltatime;

			if(m_PlumbingTimer <= 0.0f)
			{
				m_pPlayer->PlumbingFinished();

				m_Toilettes[m_CurrentToilette]->Reset();

				m_PlumbingTimer = 0.0f;

				if(m_NumActivatedToilettes > 0)
					m_NumActivatedToilettes--;

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
		for(CToilette* pToilette : m_Toilettes)
		{
			pToilette->Render(m_pWaterTexture);
		}

		m_pPlayer->Render();

		// When there's 6 or more toilettes that are full, flash a red transparent quad over the whole screen 
		if(m_NumActivatedToilettes >= m_Toilettes.size() - 2)
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

		for(CToilette* pToilette : m_Toilettes)
		{
		//	pToilette->RenderDebug();
		}

	//	m_pPlayer->RenderDebug();
	}
}

void CGame::ActivateRandomToilette()
{
	const uint32_t	NumToilettes	= (uint32_t)m_Toilettes.size();
	uint32_t		Index			= m_RandomNumberGenerator.RandomUint(0, NumToilettes - 1);

	m_NumActivatedToilettes = 0;

	for(uint32_t i = 0; i < NumToilettes; ++i)
	{
		if(m_Toilettes[i]->GetActivated())
			m_NumActivatedToilettes++;
	}

	if(m_NumActivatedToilettes < NumToilettes)
	{
		while(m_Toilettes[Index]->GetActivated())
		{
			Index = m_RandomNumberGenerator.RandomUint(0, NumToilettes - 1);
		}

		m_Toilettes[Index]->Activate();
	}

	else
		m_State = EState::ROUND_ENDED;
}

void CGame::OnPlumbingStart(const uint32_t ToiletteID)
{
	m_PlumbingTimer = m_PlumbingTimerDefault;

	m_CurrentToilette = ToiletteID;

	m_PlumbingStarted = true;
}