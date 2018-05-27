#pragma once
#include "BaseScene.h"

class MenuScene final : public BaseScene
{
public:
	MenuScene();
	~MenuScene();

	void Initialize(GameContext* gameContext) override;
	void Update(GameContext* gameContext) override;

private:
	enum class SceneInput
	{
		Singleplayer = 0,
		MultiplayerPacman = 1,
		MultiplayerGhost = 2
	};

	//GameObjects
	dae::GameObject* m_pTitleText = nullptr;
	dae::GameObject* m_pCreatorText = nullptr;
	dae::GameObject* m_pInstructionText1 = nullptr;
	dae::GameObject* m_pInstructionText2 = nullptr;
	dae::GameObject* m_pInstructionText3 = nullptr;
};

