#pragma once

enum class InputState
{
	Pressed,
	Down,
	Release
};

class InputAction
{
public:
	InputAction();
	InputAction(int actionIdx, int playerIdx = 0, InputState inputState = InputState::Pressed, int keyboardButton = -1, int mouseButton = -1, WORD gamepadButton = 0);
	~InputAction();

	int ActionIndex;
	int PlayerIndex;
	InputState InputState;
	int KeyboardButton;
	int MouseButton;
	WORD GamepadButton;
	bool IsTriggered; //true when action should be executed
	bool IsDown; //true when button is pressed
};

