#pragma once

class CGame
{
public:

	CGame();
	~CGame();

	bool Create();
	void Destroy();

	void Update(const float Deltatime);
	void Render();
	void RenderDebug();

private:

};