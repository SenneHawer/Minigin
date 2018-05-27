#include "MiniginPCH.h"
#include "InputAction.h"


InputAction::InputAction()
	:ActionIndex(0)
	,PlayerIndex(0)
	,InputState(InputState::Pressed)
	,KeyboardButton(-1)
	,MouseButton(-1)
	,GamepadButton(0)
	,IsTriggered(false)
	,IsDown(false)
{
}

InputAction::InputAction(int actionIdx, int playerIdx, enum InputState inputState, int keyboardButton, int mouseButton, WORD gamepadButton)
	:ActionIndex(actionIdx)
	, PlayerIndex(playerIdx)
	, InputState(inputState)
	, KeyboardButton(keyboardButton)
	, MouseButton(mouseButton)
	, GamepadButton(gamepadButton)
	, IsTriggered(false)
	, IsDown(false)
{
}


InputAction::~InputAction()
{
}
