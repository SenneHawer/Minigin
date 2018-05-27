#pragma once
#include "BaseScene.h"
#include "Vector2f.h"

class LevelTestScene final : public BaseScene
{
public:
	LevelTestScene();
	~LevelTestScene();

	virtual void Initialize(GameContext* gameContext) override;
	virtual void Update(GameContext* gameContext) override;

private:
	dae::GameObject* m_pPlayer = nullptr;
	dae::GameObject* m_pWall1 = nullptr;
	dae::GameObject* m_pWall2 = nullptr;
	dae::GameObject* m_pWall3 = nullptr;

	enum class MoveState
	{
		Left = 0,
		Right = 1,
		Up = 2,
		Down = 3,
		Idle = 4
	};

	float m_Speed = 100.0f;
	sen::Vector2f m_Velocity{ 0.0f, 0.0f };
	MoveState m_MoveState = MoveState::Idle;

	bool wasInside = false;

	//Helper Functions
	void UpdateInput(GameContext* gameContext);
	void UpdateCollisions(dae::GameObject* otherObj);
};

