#pragma once

class CTimer
{
public:

	 CTimer					(void);
	~CTimer					(void);

public:

	void	Update			(void);

public:

	double	GetDeltaTime	(void)	const			{return m_DeltaTime;}

	double	GetLifeTime		(void)	const			{return m_LifeTime;}

	bool	GetIsPaused		(void)	const			{return m_IsPaused;}
	void	SetIsPaused		(const bool IsPaused)	{m_IsPaused = IsPaused;}

private:

	double	m_OldTime;
	double	m_NewTime;
	double	m_DeltaTime;
	double	m_LifeTime;

	bool	m_IsPaused;

};