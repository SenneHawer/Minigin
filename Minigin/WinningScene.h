#pragma once
#include "BaseScene.h"
class GameContext;

class WinningScene final : public BaseScene
{
public:
	WinningScene();
	virtual ~WinningScene();

	virtual void Initialize(GameContext* gameContext) override;
	virtual void Update(GameContext* gameContext) override { UNREFERENCED_PARAMETER(gameContext); }

private:
	dae::GameObject* m_pWinningText = nullptr;
};

