#include "Timer.h"

#include <SDL.h>
#include <algorithm>

CTimer::CTimer(void)
: m_OldTime(0.0)
, m_NewTime(0.0)
, m_DeltaTime(0.0)
, m_LifeTime(0.0)
, m_IsPaused(false)
{
	m_OldTime = SDL_GetTicks();
	m_NewTime = SDL_GetTicks();
}

CTimer::~CTimer(void)
{

}

void CTimer::Update(void)
{
	m_NewTime			 = (double)SDL_GetTicks();
	const double Delta	 = (m_NewTime - m_OldTime) * 0.001;
	m_DeltaTime			 = std::min(Delta * (m_IsPaused ? 0.0 : 1.0), 0.25);
	m_OldTime			 = m_NewTime;
	m_LifeTime			+= Delta;
}