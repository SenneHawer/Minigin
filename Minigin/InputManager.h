#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "InputAction.h"
#include <map>

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};


	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;

		void AddInputAction(InputAction inputAction);
		void ClearInputActions();

		void Update();
		bool IsActionTriggered(int playerIdx, int actionIdx);

	private:
		//Keyboard
		BYTE *m_pCurrKeyboardState, *m_pOldKeyboardState, *m_pKeyboardState0, *m_pKeyboardState1;
		bool m_IsKeyboardActive;
		int debugCount = 0;
		//Gamepad
		XINPUT_STATE m_OldGamepadState[XUSER_MAX_COUNT], m_CurrGamepadState[XUSER_MAX_COUNT];
		bool m_ConnectedGamepads[XUSER_MAX_COUNT];

		//std::vector<InputAction> m_InputActions;
		//std::map<int, std::vector<InputAction>> m_InputActions;
		std::map<int, std::vector<InputAction>> m_InputActions;


		//HELPER FUNCTIONS
		void UpdateKeyboardStates();
		void UpdateGamePadStates();

		bool IsKeyboardKeyPressed(int key, bool usePreviousframe);
		bool IsGamepadButtomPressed(WORD button, int playerIndex, bool usePreviousframe);

		void RefreshControllerConnections();
	};

}
