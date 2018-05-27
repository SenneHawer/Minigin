#pragma once
#include "BaseScene.h"
#include "Vector2f.h"
#include "Level.h"

class CollisionTestScene final : public BaseScene
{
public:
	CollisionTestScene();
	~CollisionTestScene();

	virtual void Initialize(GameContext* gameContext) override;
	virtual void Update(GameContext* gameContext) override;

private:
	dae::GameObject* m_pObj1 = nullptr;
	dae::GameObject* m_pObj2 = nullptr;

	Level* m_pLevel = nullptr;

	enum class MoveState
	{
		Left = 0,
		Right = 1,
		Up = 2,
		Down = 3,
		Idle = 4
	};

	float m_Speed = 100.0f;
	sen::Vector2f m_Velocity{0.0f, 0.0f};
	MoveState m_MoveState = MoveState::Idle;

	bool wasInside = false;
};

