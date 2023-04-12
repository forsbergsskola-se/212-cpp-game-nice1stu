#pragma once

#include "Framework/Texture.h"

class CLevel
{
public:

	CLevel();
	~CLevel();

	bool Create();
	void Destroy();

	void Render();
	void RenderDebug();

private:

	CTexture* m_pTexture;

};