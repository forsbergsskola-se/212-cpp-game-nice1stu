#include "Application.h"

#include "Framework/InputHandler.h"
#include "Framework/RenderDevice.h"
#include "Framework/TextureFactory.h"

CApplication::CApplication()
: m_pTimer(nullptr)
, m_pGame(nullptr)
, m_Running(true)
{

}

CApplication::~CApplication()
{

}

bool CApplication::Create(void)
{
#ifdef _DEBUG
	printf("Info: creating application\n");
#endif

	CRenderDevice::Initialize();
	if(!CRenderDevice::GetInstance().Create(CVector2D(1280.0f, 720.0f), "Plunger Bob"))
		return false;

	CTextureFactory::Initialize();
	if(!CTextureFactory::GetInstance().Create("Data/Textures/"))
		return false;

	CInputHandler::Initialize();

	m_pTimer = new CTimer;

	m_pGame = new CGame;

	if (!m_pGame->Create())
	{
		printf("Error: Failed to create game\n");

		return false;
	}

	return true;
}

void CApplication::Destroy(void)
{
#ifdef _DEBUG
	printf("Info: destroying application\n");
#endif

	m_pGame->Destroy();
	delete m_pGame;
	m_pGame = nullptr;

	delete m_pTimer;
	m_pTimer = nullptr;

	CInputHandler::Deinitialize();

	CTextureFactory::GetInstance().Destroy();
	CTextureFactory::Deinitialize();

	CRenderDevice::GetInstance().Destroy();
	CRenderDevice::Deinitialize();
}

void CApplication::Run()
{
	CRenderDevice& rRenderDevice = CRenderDevice::GetInstance();

	while (m_Running)
	{
		Update();
		Render();

		rRenderDevice.Sleep(1);
	}
}

void CApplication::Update()
{
	SDL_Event Event;

	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
			case SDL_QUIT:
			{
				Quit();

				break;
			}

			default:
				break;
		}
	}

	CInputHandler::GetInstance().Update();

	m_pTimer->Update();

	m_pGame->Update((float)m_pTimer->GetDeltaTime());
}

void CApplication::Render()
{
	CRenderDevice& rRenderDevice = CRenderDevice::GetInstance();

	if(rRenderDevice.BeginRender())
	{
		m_pGame->Render();

	#ifdef _DEBUG
		m_pGame->RenderDebug();
	#endif

		rRenderDevice.EndRender();
	}
}