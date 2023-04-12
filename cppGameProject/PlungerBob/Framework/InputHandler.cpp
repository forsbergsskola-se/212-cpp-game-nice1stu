#include "InputHandler.h"

CInputHandler::CInputHandler(void)
{
#ifdef _DEBUG
	printf("Info: creating input handler\n");
#endif
}

CInputHandler::~CInputHandler(void)
{
#ifdef _DEBUG
	printf("Info: destroying input handler\n");
#endif
}

void CInputHandler::Update(void)
{
	// Process the keyboard state

	const Uint8* pKeyboardState = SDL_GetKeyboardState(nullptr);

	for(uint32_t i = 0; i < NUM_KEYBOARD_KEYS; ++i)
	{
		m_Keyboard.PreviousKeyState[i]	= m_Keyboard.CurrentKeyState[i];
		m_Keyboard.CurrentKeyState[i]	= (pKeyboardState[i] == SDL_TRUE);
	}

	// Process the mouse state

	int32_t			MouseX		= 0;
	int32_t			MouseY		= 0;
	const Uint32	MouseState	= SDL_GetMouseState(&MouseX, &MouseY);

	for(uint32_t i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		m_Mouse.PreviousButtonState[i]	= m_Mouse.CurrentButtonState[i];
		m_Mouse.CurrentButtonState[i]	= ((MouseState & SDL_BUTTON(i)) ? true : false);
	}

	m_Mouse.Position = CVector2D((float)MouseX, (float)MouseY);

	const CVector2D PrevMousePos	= m_Mouse.Position;
	const CVector2D NewMousePos		= CVector2D((float)MouseX, (float)MouseY);

	m_Mouse.Position		= NewMousePos;
	m_Mouse.DeltaMovement	= NewMousePos - PrevMousePos;
}

bool CInputHandler::KeyPressed(const uint32_t Key) const
{
	if(Key > (NUM_KEYBOARD_KEYS - 1))
		return false;

	return (m_Keyboard.CurrentKeyState[Key] && !m_Keyboard.PreviousKeyState[Key]);
}

bool CInputHandler::KeyHeld(const uint32_t Key) const
{
	if(Key > (NUM_KEYBOARD_KEYS - 1))
		return false;

	return m_Keyboard.CurrentKeyState[Key];
}

bool CInputHandler::KeyReleased(const uint32_t Key) const
{
	if(Key > (NUM_KEYBOARD_KEYS - 1))
		return false;

	return (!m_Keyboard.CurrentKeyState[Key] && m_Keyboard.PreviousKeyState[Key]);
}

bool CInputHandler::MouseButtonPressed(const uint32_t Button) const
{
	if(Button > (NUM_MOUSE_BUTTONS - 1))
		return false;

	return (m_Mouse.CurrentButtonState[Button] && !m_Mouse.PreviousButtonState[Button]);
}

bool CInputHandler::MouseButtonHeld(const uint32_t Button) const
{
	if(Button > (NUM_MOUSE_BUTTONS - 1))
		return false;

	return m_Mouse.CurrentButtonState[Button];
}

bool CInputHandler::MouseButtonReleased(const uint32_t Button) const
{
	if(Button > (NUM_MOUSE_BUTTONS - 1))
		return false;

	return (!m_Mouse.CurrentButtonState[Button] && m_Mouse.PreviousButtonState[Button]);
}