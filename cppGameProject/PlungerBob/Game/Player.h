#pragma once

#include "Framework/Texture.h"

class CPlayer
{
public:

	CPlayer();
	~CPlayer();

	bool Create();
	void Destroy();

	void HandleInput();

	void Render();
	void RenderDebug();

private:
	CTexture* m_pTexture;


};