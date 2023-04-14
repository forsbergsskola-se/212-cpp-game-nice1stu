#include "Level.h"

#include "Framework/RenderDevice.h"
#include "Framework/TextureFactory.h"

CLevel::CLevel(void)
: m_pTexture(nullptr)
{
	m_CollisionQuads.clear();
	m_TriggerQuads.clear();
}

CLevel::~CLevel(void)
{

}

bool CLevel::Create(void)
{
	m_pTexture = CTextureFactory::GetInstance().CreateTexture("Room.png");

	const CVector2D WindowSize = CRenderDevice::GetInstance().GetWindow()->GetSize();

	// Top, bottom, left and right outer walls
	m_CollisionQuads.push_back({0.0f,					0.0f,					WindowSize.x,	100.0f});
	m_CollisionQuads.push_back({0.0f,					WindowSize.y - 100.0f,	WindowSize.x,	100.0f});
	m_CollisionQuads.push_back({0.0f,					100.0f,					110.0f,			520.0f});
	m_CollisionQuads.push_back({WindowSize.x - 110.0f,	100.0f,					110.0f,			520.0f});

	// Top vertical inner walls
	m_CollisionQuads.push_back({210.0f,					100.0f,					120.0f,			192.0f});
	m_CollisionQuads.push_back({440.0f,					100.0f,					120.0f,			192.0f});
	m_CollisionQuads.push_back({720.0f,					100.0f,					120.0f,			192.0f});
	m_CollisionQuads.push_back({950.0f,					100.0f,					120.0f,			192.0f});

	// Bottom vertical inner walls
	m_CollisionQuads.push_back({210.0f,					430.0f,					120.0f,			192.0f});
	m_CollisionQuads.push_back({445.0f,					430.0f,					120.0f,			192.0f});
	m_CollisionQuads.push_back({720.0f,					430.0f,					120.0f,			192.0f});
	m_CollisionQuads.push_back({955.0f,					430.0f,					120.0f,			192.0f});

	// Top toilets
	m_ToiletteQuads.push_back({142.0f,					100.0f,					60.0f,			105.0f});
	m_ToiletteQuads.push_back({375.0f,					100.0f,					60.0f,			105.0f});
	m_ToiletteQuads.push_back({843.0f,					100.0f,					60.0f,			105.0f});
	m_ToiletteQuads.push_back({1076.0f,					100.0f,					60.0f,			105.0f});

	// Bottom toilets
	m_ToiletteQuads.push_back({142.0f,					515.0f,					60.0f,			105.0f});
	m_ToiletteQuads.push_back({375.0f,					515.0f,					60.0f,			105.0f});
	m_ToiletteQuads.push_back({843.0f,					515.0f,					60.0f,			105.0f});
	m_ToiletteQuads.push_back({1076.0f,					515.0f,					60.0f,			105.0f});

	// Top toilettes triggers
	m_TriggerQuads.push_back({142.0f,					205.0f,					60.0f,			10.0f});
	m_TriggerQuads.push_back({375.0f,					205.0f,					60.0f,			10.0f});
	m_TriggerQuads.push_back({843.0f,					205.0f,					60.0f,			10.0f});
	m_TriggerQuads.push_back({1076.0f,					205.0f,					60.0f,			10.0f});

	// Bottom toilettes triggers
	m_TriggerQuads.push_back({142.0f,					505.0f,					60.0f,			10.0f});
	m_TriggerQuads.push_back({375.0f,					505.0f,					60.0f,			10.0f});
	m_TriggerQuads.push_back({843.0f,					505.0f,					60.0f,			10.0f});
	m_TriggerQuads.push_back({1076.0f,					505.0f,					60.0f,			10.0f});

	return true;
}

void CLevel::Destroy(void)
{
	m_CollisionQuads.clear();
	m_ToiletteQuads.clear();
	m_TriggerQuads.clear();

	CTextureFactory::GetInstance().DestroyTexture(m_pTexture->GetName());
}

void CLevel::Render(void)
{
	CRenderDevice::GetInstance().RenderCopy(m_pTexture);
}

void CLevel::RenderDebug(void)
{
	CRenderDevice& rRenderDevice = CRenderDevice::GetInstance();

	rRenderDevice.SetRenderDrawColor({200, 0, 0, 100});

	for(const SDL_FRect& rQuad : m_CollisionQuads)
	{
		rRenderDevice.RenderQuad(rQuad, true);
	}

	for(const SDL_FRect& rQuad : m_ToiletteQuads)
	{
		rRenderDevice.RenderQuad(rQuad, true);
	}

	rRenderDevice.SetRenderDrawColor({0, 200, 0, 100});

	for(const SDL_FRect& rQuad : m_TriggerQuads)
	{
		rRenderDevice.RenderQuad(rQuad, true);
	}
}