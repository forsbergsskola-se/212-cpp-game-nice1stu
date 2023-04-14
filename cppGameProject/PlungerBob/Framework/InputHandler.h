#pragma once

#include "Singleton.h"
#include "Vector2D.h"

#include <SDL.h>
#include <memory.h>

#define NUM_KEYBOARD_KEYS (SDL_NUM_SCANCODES)
#define NUM_MOUSE_BUTTONS (8)

class CInputHandler : public CSingleton<CInputHandler>
{
	// Keyboard state struct

	struct SKeyboard
	{
		SKeyboard(void)
		{
			memset(CurrentKeyState,		false, sizeof(CurrentKeyState));
			memset(PreviousKeyState,	false, sizeof(PreviousKeyState));
		}

		bool CurrentKeyState[NUM_KEYBOARD_KEYS];
		bool PreviousKeyState[NUM_KEYBOARD_KEYS];
	};

	// Mouse state struct

	struct SMouse
	{
		SMouse(void)
		: Position(CVector2D::Zero)
		, DeltaMovement(CVector2D::Zero)
		{
			memset(CurrentButtonState,	false, sizeof(CurrentButtonState));
			memset(PreviousButtonState,	false, sizeof(PreviousButtonState));
		}

		CVector2D	Position;
		CVector2D	DeltaMovement;
		bool		CurrentButtonState[NUM_MOUSE_BUTTONS];
		bool		PreviousButtonState[NUM_MOUSE_BUTTONS];
	};

public:

	 CInputHandler					(void);
	~CInputHandler					(void);

	void		Update				(void);

	bool		KeyPressed			(const uint32_t Key) const;
	bool		KeyHeld				(const uint32_t Key) const;
	bool		KeyReleased			(const uint32_t Key) const;

	bool		MouseButtonPressed	(const uint32_t Button) const;
	bool		MouseButtonHeld		(const uint32_t Button) const;
	bool		MouseButtonReleased	(const uint32_t Button) const;

public:

	CVector2D&	GetMousePosition	(void)	const	{return (CVector2D&)m_Mouse.Position;}

private:

	SKeyboard	m_Keyboard;

	SMouse		m_Mouse;

};