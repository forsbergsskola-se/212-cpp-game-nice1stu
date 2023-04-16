#include "TextureHandler.h"

#include "Application.h"
#include "StringUtilities.h"

#include <SDL_image.h>

CTextureHandler::CTextureHandler(void)
: m_BasePath("")
{
	m_TextureMap.clear();
}

CTextureHandler::~CTextureHandler(void)
{

}

bool CTextureHandler::Create(const std::string& rBasePath)
{
#ifdef _DEBUG
	printf("Info: creating texture handler\n");
#endif

	if(IMG_Init(IMG_INIT_PNG) == 0)
	{
	#ifdef _DEBUG
		printf("Error: failed to initialize SDL Image. %s\n", IMG_GetError());
	#endif

		return false;
	}

	m_BasePath = rBasePath;

	CTexture* pDefaultTexture = CreateTexture("Default.png");

	if(!pDefaultTexture)
		return false;

	m_TextureMap["DefaultTexture"] = pDefaultTexture;

	return true;
}

void CTextureHandler::Destroy(void)
{
#ifdef _DEBUG
	printf("Info: destroying texture handler\n");
#endif

	DestroyTexture("DefaultTexture");

	m_TextureMap.clear();

	IMG_Quit();
}

CTexture* CTextureHandler::CreateTexture(const std::string& rFileName)
{
	if(rFileName.empty())
		m_TextureMap.find("DefaultTexture")->second;

	const std::string FileName = RemoveFileExtension(rFileName);

	TextureMap::const_iterator FindIt = m_TextureMap.find(FileName);

	if(FindIt != m_TextureMap.end())
	{
		FindIt->second->m_ReferenceCount++;

		return FindIt->second;
	}

	CTexture* pTexture = new CTexture;

	if(!pTexture->Create(rFileName))
	{
		delete pTexture;
		pTexture = nullptr;

		return (!m_TextureMap.empty() ? m_TextureMap.find("DefaultTexture")->second : nullptr); 
	}

	pTexture->m_ReferenceCount++;

	m_TextureMap[FileName] = pTexture;

	return pTexture;
}

void CTextureHandler::DestroyTexture(const std::string& rName)
{
	if(rName.empty())
		return;

	TextureMap::iterator FindIt = m_TextureMap.find(rName);

	if(FindIt == m_TextureMap.end())
	{
	#ifdef _DEBUG
		const std::string Message = "Error: failed to destroy texture '" + rName + "' - texture not found";

		printf("%s\n", Message.c_str());
	#endif

		return;
	}

	if(FindIt->second->m_ReferenceCount > 0)
		FindIt->second->m_ReferenceCount--;

	if(FindIt->second->m_ReferenceCount != 0)
		return;

	FindIt->second->Destroy();
	delete FindIt->second;
	FindIt->second = nullptr;

	m_TextureMap.erase(FindIt);
}