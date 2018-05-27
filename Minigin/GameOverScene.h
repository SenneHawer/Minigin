#pragma once
#include "BaseScene.h"
class GameContext;

class GameOverScene final : public BaseScene
{
public:
	GameOverScene();
	~GameOverScene();

	void Initialize(GameContext* gameContext) override;
	void Update(GameContext* gameContext) override;

private:
	dae::GameObject* m_pGameOverText = nullptr;
};

