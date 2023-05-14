#pragma once

class CTimer
{
public:

	 CTimer					(void);
	~CTimer					(void);

public:

	void	Update			(void);

public:

	double	GetDeltaTime	(void) const {return m_DeltaTime;}

	double	GetLifeTime		(void) const {return m_LifeTime;}

private:

	double	m_OldTime;
	double	m_NewTime;
	double	m_DeltaTime;
	double	m_LifeTime;

};