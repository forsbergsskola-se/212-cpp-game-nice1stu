#include "Texture.h"

#include "RenderDevice.h"
#include "StringUtilities.h"
#include "TextureFactory.h"

#include <SDL_image.h>

CTexture::CTexture(void)
: m_pTexture(nullptr)
, m_pClipQuad(nullptr)
, m_FlipMethod(SDL_RendererFlip::SDL_FLIP_NONE)
, m_Position(CVector2D::Zero)
, m_Size(CVector2D::Zero)
, m_Angle(0.0f)
, m_ReferenceCount(0)
, m_Name("")
{

}

CTexture::~CTexture(void)
{

}

bool CTexture::Create(const std::string& rFileName)
{
	const std::string Name = RemoveFileExtension(rFileName);

#ifdef _DEBUG
	printf("Info: creating texture '%s'\n", Name.c_str());
#endif

	const std::string FileName = CTextureFactory::GetInstance().GetBasePath() + rFileName;

	SDL_Surface* pSurface = IMG_Load(FileName.c_str());

	if(!pSurface)
	{
	#ifdef _DEBUG
		printf("Error: failed to load image file '%s'. '%s'\n", rFileName.c_str(), IMG_GetError());
	#endif

		return false;
	}

	m_pTexture = SDL_CreateTextureFromSurface(CRenderDevice::GetInstance().GetRenderer(), pSurface);

	if(!m_pTexture)
	{
	#ifdef _DEBUG
		printf("Error: failed to create texture '%s'. '%s'\n", Name.c_str(), SDL_GetError());
	#endif

		SDL_FreeSurface(pSurface);
		pSurface = nullptr;

		return false;
	}

	SDL_FreeSurface(pSurface);
	pSurface = nullptr;

	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);

	int32_t TextureWidth	= 0;
	int32_t TextureHeight	= 0;

	SDL_QueryTexture(m_pTexture, NULL, NULL, &TextureWidth, &TextureHeight);

	m_Size = CVector2D((float)TextureWidth, (float)TextureHeight);

	m_Name = Name;

	return true;
}

void CTexture::Destroy(void)
{
#ifdef _DEBUG
	printf("Info: destroying texture '%s'\n", m_Name.c_str());
#endif

	delete m_pClipQuad;
	m_pClipQuad = nullptr;

	SDL_DestroyTexture(m_pTexture);
	m_pTexture = nullptr;
}

void CTexture::SetTextureCoords(const uint32_t Left, const uint32_t Right, const uint32_t Top, const uint32_t Bottom)
{
	if(!m_pClipQuad)
		m_pClipQuad = new SDL_Rect;

	m_pClipQuad->x = Left;
	m_pClipQuad->y = Top;
	m_pClipQuad->w = Right	- Left;
	m_pClipQuad->h = Bottom - Top;
}