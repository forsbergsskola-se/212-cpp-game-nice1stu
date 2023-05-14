#pragma once

#include "Game/Game.h"

#include "Framework/Singleton.h"
#include "Framework/Timer.h"

class CApplication : public CSingleton<CApplication>
{
public:

	 CApplication		(void);
	~CApplication		(void);

	bool	Create		(void);
	void	Destroy		(void);

	void	Run			(void);

	void	Update		(void);
	void	Render		(void);

	void	Quit		(void) {m_Running = false;}

public:

	CTimer*	GetTimer	(void) const {return m_pTimer;}

private:

	CTimer*	m_pTimer;

	CGame*	m_pGame;

	bool	m_Running;

};