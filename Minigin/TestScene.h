#pragma once
#include "BaseScene.h"
#include "Vector2f.h"

class TestScene final : public BaseScene
{
public:
	TestScene();
	~TestScene();

	virtual void Initialize(GameContext* gameContext) override;
	virtual void Update(GameContext* gameContext) override;

private:

	dae::GameObject* m_pTestObj = nullptr;
	dae::GameObject* m_pTestObj2 = nullptr;

	dae::GameObject* m_pText = nullptr;

	sen::Vector2f m_Velocity{ 100.0f, 0 };

};

