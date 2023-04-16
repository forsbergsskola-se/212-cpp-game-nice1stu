#pragma once

#include "Singleton.h"
#include "Texture.h"

#include <map>
#include <string>

class CTextureHandler : public CSingleton<CTextureHandler>
{
public:

	 CTextureHandler				(void);
	~CTextureHandler				(void);

	bool			Create			(const std::string& rBasePath);
	void			Destroy			(void);

	CTexture*		CreateTexture	(const std::string& rFileName);
	void			DestroyTexture	(const std::string& rName);

public:

	std::string&	GetBasePath		(void) const {return (std::string&)m_BasePath;}

private:

	typedef std::map<std::string, CTexture*> TextureMap;

private:

	std::string	m_BasePath;

	TextureMap	m_TextureMap;

};