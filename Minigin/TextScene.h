#pragma once
#include "BaseScene.h"

class TextScene final : public BaseScene
{
public:
	TextScene();
	~TextScene();

	void Initialize(GameContext* gameContext) override;
	void Update(GameContext* gameContext) override;

private:
	dae::GameObject* m_pText;

};

