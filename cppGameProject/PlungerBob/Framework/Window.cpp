#include "Window.h"

CWindow::CWindow(void)
: m_pWindow(nullptr)
, m_Center(CVector2D::Zero)
, m_Size(CVector2D::Zero)
{

}

CWindow::~CWindow(void)
{

}

bool CWindow::Create(const CVector2D& rSize, const std::string& rTitle)
{
#ifdef _DEBUG
	printf("Info: creating window\n");
#endif

	m_pWindow = SDL_CreateWindow(rTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int32_t)rSize.x, (int32_t)rSize.y, SDL_WINDOW_SHOWN);

	if(!m_pWindow)
	{
	#ifdef _DEBUG
		printf("Error: failed to create window. %s\n", SDL_GetError());
	#endif

		return false;
	}

	SDL_WarpMouseInWindow(m_pWindow, (int32_t)(rSize.x * 0.5f), (int32_t)(rSize.y * 0.5f));

	m_Center	= rSize * 0.5f;
	m_Size		= rSize;

	return true;
}

void CWindow::Destroy(void)
{
#ifdef _DEBUG
	printf("Info: destroying window\n");
#endif

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
}

bool CWindow::SetTitle(const std::string& rTitle)
{
	if(rTitle.empty())
		return false;

	SDL_SetWindowTitle(m_pWindow, rTitle.c_str());

	return true;
}