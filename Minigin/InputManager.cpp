#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <algorithm>
#include <minwinbase.h>

//PBYTE dae::InputManager::CurrentKeyboardState = nullptr;

dae::InputManager::InputManager()
	:m_pCurrKeyboardState(nullptr)
	, m_pOldKeyboardState(nullptr)
	, m_pKeyboardState0(nullptr)
	, m_pKeyboardState1(nullptr)
	, m_IsKeyboardActive(true)
{
	m_pKeyboardState0 = new BYTE[256];
	m_pKeyboardState1 = new BYTE[256];

	GetKeyboardState(m_pKeyboardState0);
	GetKeyboardState(m_pKeyboardState1);

	RefreshControllerConnections();
}

dae::InputManager::~InputManager()
{
	if (m_pKeyboardState0 != nullptr)
	{
		delete[] m_pKeyboardState0;
		delete[] m_pKeyboardState1;

		m_pKeyboardState0 = nullptr;
		m_pKeyboardState1 = nullptr;
		m_pCurrKeyboardState = nullptr;
		m_pOldKeyboardState = nullptr;
	}
}


bool dae::InputManager::ProcessInput()
{
	//ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	//XInputGetState(0, &currentState);


	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	UNREFERENCED_PARAMETER(button);
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrGamepadState->Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrGamepadState->Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrGamepadState->Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrGamepadState->Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

void dae::InputManager::Update()
{
	UpdateKeyboardStates();
	UpdateGamePadStates();

	//std::for_each(m_InputActions.begin(), m_InputActions.end(), [&](InputAction& action)

	for (auto & actionVector : m_InputActions)
	{
		for (auto& action : actionVector.second)
		{
			auto& currAction = action;

			//Reset isTriggered
			currAction.IsTriggered = false;

			switch (currAction.InputState)
			{
			case InputState::Pressed:
				//Keyboard
				if (currAction.KeyboardButton > 0x07 && currAction.KeyboardButton <= 0xFE) //Is key valid?
				{
					if (!IsKeyboardKeyPressed(currAction.KeyboardButton, true)) //key not pressed prev Frame?
						if (IsKeyboardKeyPressed(currAction.KeyboardButton, false)) //key pressed this Frame?
						{
							currAction.IsTriggered = true;	//If key was not pressed prev frame but it is this frame => trigger is true
														//Next frame this will not be true, isTriggered will be set to false at the top of this function.
							/*++debugCount;
							std::cout << debugCount << std::endl;*/
						}
				}
				//Gamepad
				if (!currAction.IsTriggered && currAction.GamepadButton != 0)
				{
					if (!IsGamepadButtomPressed(currAction.GamepadButton, currAction.PlayerIndex, true))
						if (IsGamepadButtomPressed(currAction.GamepadButton, currAction.PlayerIndex, false))
						{
							currAction.IsTriggered = true;
						}
				}
				break;

			case InputState::Down:
				//KeyBoard
				if (currAction.KeyboardButton > 0x07 && currAction.KeyboardButton <= 0xFE)
				{
					if (IsKeyboardKeyPressed(currAction.KeyboardButton, true))
						if (IsKeyboardKeyPressed(currAction.KeyboardButton, false))
						{
							currAction.IsTriggered = true;
						}
				}
				//Gamepad
				if (!currAction.IsTriggered && currAction.GamepadButton != 0)
				{
					if (IsGamepadButtomPressed(currAction.GamepadButton, currAction.PlayerIndex, true))
						if (IsGamepadButtomPressed(currAction.GamepadButton, currAction.PlayerIndex, false))
						{
							currAction.IsTriggered = true;
						}
				}
				break;

			case InputState::Release:
				//KeyBoard
				if (currAction.KeyboardButton > 0x07 && currAction.KeyboardButton <= 0xFE)
				{
					if (IsKeyboardKeyPressed(currAction.KeyboardButton, true))
						if (!IsKeyboardKeyPressed(currAction.KeyboardButton, false))
						{
							currAction.IsTriggered = true;
						}
				}
				//Gamepad
				if (!currAction.IsTriggered && currAction.GamepadButton != 0)
				{
					if (IsGamepadButtomPressed(currAction.GamepadButton, currAction.PlayerIndex, true))
						if (!IsGamepadButtomPressed(currAction.GamepadButton, currAction.PlayerIndex, false))
						{
							currAction.IsTriggered = true;
						}
				}
				break;
			}
		}
	}
}


void dae::InputManager::AddInputAction(InputAction inputAction)
{
	//auto found = std::find_if(m_InputActions.begin(), m_InputActions.end(), [&](InputAction action)
	//{
	//	return action.ActionIndex == inputAction.ActionIndex;
	//});

	//if (found == m_InputActions.end())
	//{
	//	m_InputActions.push_back(inputAction);
	//}
	//else
	//{
	//	std::cout << "Cannot have 2 Action with same index!" << std::endl;
	//}

	//m_InputActions[inputAction.ActionIndex].push_back(inputAction);

	//m_InputActions[inputAction.PlayerIndex] = inputAction;
	m_InputActions[inputAction.PlayerIndex].push_back(inputAction);

}

void dae::InputManager::ClearInputActions()
{
	m_InputActions.clear();
}


bool dae::InputManager::IsActionTriggered(int playerIdx, int actionIdx)
{
	//auto found = std::find_if(m_InputActions.begin(), m_InputActions.end(), [&](InputAction action)
	//{
	//	return action.ActionIndex == actionIdx;
	//});

	//bool result = false;

	//if (found != m_InputActions.end())
	//{
	//	result = found->IsTriggered;
	//}

	//return result;

	//if (m_InputActions.at(actionIdx).IsTriggered)
	//{
	//	return true;
	//}
	//else
	//	return false;

	//for (InputAction action : m_InputActions[actionIdx])
	//{
	//	if (action.IsTriggered == true)
	//		return true;
	//}

	//return false;

	if (m_InputActions[playerIdx].at(actionIdx).IsTriggered)
	{
		return true;
	}
	else
		return false;

}


//HELPER FUCNTIONS
void dae::InputManager::UpdateKeyboardStates()
{
	BOOL keyboardResult;

	if (m_IsKeyboardActive)
	{
		keyboardResult = GetKeyboardState(m_pKeyboardState1);
		m_pOldKeyboardState = m_pKeyboardState0;
		m_pCurrKeyboardState = m_pKeyboardState1;
	}
	else
	{
		keyboardResult = GetKeyboardState(m_pKeyboardState0);
		m_pOldKeyboardState = m_pKeyboardState1;
		m_pCurrKeyboardState = m_pKeyboardState0;
	}

	m_IsKeyboardActive = !m_IsKeyboardActive;

}

void dae::InputManager::UpdateGamePadStates()
{
	DWORD result;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (m_ConnectedGamepads[i])
		{
			m_OldGamepadState[i] = m_CurrGamepadState[i];

			result = XInputGetState(i, &m_CurrGamepadState[i]);
			m_ConnectedGamepads[i] = (result == ERROR_SUCCESS);
		}
	}
}

bool dae::InputManager::IsKeyboardKeyPressed(int key, bool usePreviousframe)
{
	if (!m_pOldKeyboardState | !m_pCurrKeyboardState)
		return false;

	if (!(key > 0x07 && key <= 0xFE))
		return false;

	if (usePreviousframe)
		return (m_pOldKeyboardState[key] & 0xF0) != 0;
	else
		return (m_pCurrKeyboardState[key] & 0xF0) != 0;
}
bool dae::InputManager::IsGamepadButtomPressed(WORD button, int playerIndex, bool usePreviousframe)
{
	if (!m_ConnectedGamepads[playerIndex])
		return false;


	if (usePreviousframe)
	{
		return (m_OldGamepadState[playerIndex].Gamepad.wButtons & button) != 0;
	}
	else
	{
		return (m_CurrGamepadState[playerIndex].Gamepad.wButtons & button) != 0;
	}
}

void dae::InputManager::RefreshControllerConnections()
{
	DWORD result;
	for (DWORD i{}; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		result = XInputGetState(i, &state);
		m_ConnectedGamepads[i] = (result == ERROR_SUCCESS);
	}
}
