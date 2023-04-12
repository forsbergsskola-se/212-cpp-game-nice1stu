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
	void Update(const float Deltatime);

	void Render();
	void RenderDebug();

private:
	CTexture* m_pTexture;

	CVector2D m_Position;
	CVector2D m_Velocity;
	CVector2D m_Speed;




};