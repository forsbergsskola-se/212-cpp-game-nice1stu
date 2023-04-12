#include "RenderDevice.h"

#include "MathUtilities.h"

CRenderDevice::CRenderDevice(void)
: m_pWindow(nullptr)
, m_pRenderer(nullptr)
, m_ClearColor({0, 0, 0, 0})
{

}

CRenderDevice::~CRenderDevice(void)
{

}

bool CRenderDevice::Create(const CVector2D& rWindowSize, const std::string& rWindowTitle)
{
#ifdef _DEBUG
	printf("Info: creating render device\n");
#endif

#ifdef _DEBUG
	printf("Info: initializing SDL\n");
#endif

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
	#ifdef _DEBUG
		printf("Error: failed to initialize SDL. %s\n", SDL_GetError());
	#endif

		return false;
	}

	m_pWindow = new CWindow;
	if(!m_pWindow->Create(rWindowSize, rWindowTitle))
		return false;

#ifdef _DEBUG
	printf("Info: initializing SDL renderer\n");
#endif

	m_pRenderer = SDL_CreateRenderer(m_pWindow->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(!m_pRenderer)
	{
	#ifdef _DEBUG
		printf("Error: failed to create SDL renderer. %s\n", SDL_GetError());
	#endif

		return false;
	}

	SDL_SetRenderDrawColor(m_pRenderer, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
	SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

	SDL_RenderClear(m_pRenderer);
	SDL_RenderPresent(m_pRenderer);

	return true;
}

void CRenderDevice::Destroy(void)
{
#ifdef _DEBUG
	printf("Info: destroying render device\n");
#endif

	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = nullptr;

	m_pWindow->Destroy();
	delete m_pWindow;
	m_pWindow = nullptr;

	SDL_Quit();
}

bool CRenderDevice::BeginRender(void)
{
	if(SDL_SetRenderDrawColor(m_pRenderer, m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a) == -1)
		return false;

	if(SDL_RenderClear(m_pRenderer) == -1)
		return false;

	return true;
}

void CRenderDevice::EndRender(void)
{
	SDL_RenderPresent(m_pRenderer);
}

SDL_Texture* CRenderDevice::CreateTextureFromSurface(SDL_Surface* pSurface)
{
	return SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
}

void CRenderDevice::DestroyTexture(SDL_Texture** ppTexture)
{
	if(!(*ppTexture))
		return;

	SDL_DestroyTexture(*ppTexture);
	*ppTexture = nullptr;
}

void CRenderDevice::RenderCopy(CTexture* pTexture)
{
	const CVector2D Position	= pTexture->GetPosition();
	const CVector2D Size		= pTexture->GetSize();
	const SDL_Rect*	pClipQuad	= pTexture->GetClipQuad();

	const SDL_FRect Quad = {(Position.x),								(Position.y),
							(pClipQuad ? (float)pClipQuad->w : Size.x), (pClipQuad ? (float)pClipQuad->h : Size.y)};

	SDL_RenderCopyExF(m_pRenderer, pTexture->GetTexture(), pClipQuad, &Quad, pTexture->GetAngle(), nullptr, pTexture->GetFlipMethod());
}

void CRenderDevice::RenderCopy(CTexture* pTexture, const CVector2D& rPosition)
{
	const CVector2D Size		= pTexture->GetSize();
	const SDL_Rect*	pClipQuad	= pTexture->GetClipQuad();

	const SDL_FRect Quad = {(rPosition.x),								(rPosition.y),
							(pClipQuad ? (float)pClipQuad->w : Size.x), (pClipQuad ? (float)pClipQuad->h : Size.y)};

	SDL_RenderCopyExF(m_pRenderer, pTexture->GetTexture(), pClipQuad, &Quad, pTexture->GetAngle(), nullptr, pTexture->GetFlipMethod());
}

void CRenderDevice::RenderQuad(const SDL_FRect& rQuad, const bool Filled)
{
	if(Filled)
		SDL_RenderFillRectF(m_pRenderer, &rQuad);

	else
		SDL_RenderDrawRectF(m_pRenderer, &rQuad);
}

void CRenderDevice::SetRenderDrawColor(const SDL_Color& rColor)
{
	SDL_SetRenderDrawColor(m_pRenderer, rColor.r, rColor.g, rColor.b, rColor.a);
}

bool CRenderDevice::SetWindowTitle(const std::string& rWindowTitle)
{
	return m_pWindow->SetTitle(rWindowTitle);
}

void CRenderDevice::Sleep(const uint32_t TimeMs)
{
	SDL_Delay(TimeMs);
}