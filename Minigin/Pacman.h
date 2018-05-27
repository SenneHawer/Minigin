#pragma once
#include "GameObject.h"
#include "Vector2f.h"

class Level;

class Pacman : public dae::GameObject
{
public:
	Pacman();
	virtual ~Pacman();
	virtual void Create(Level* level, int playerIdx, sen::Vector2f spawnLoc);
	virtual void Update(GameContext* gameContext) override;

	sen::Vector2f& GetDirectionRef();

	bool IsAngry();
	bool IsDead();
	void Die();
	void MakeAngry();
	int GetLives();

protected:
	enum class PlayerMovingState
	{
		Left = 0,
		Right = 1,
		Up = 2,
		Down = 3,
		Idle = 4
	};


private:
	//Viariables
	sen::Vector2f m_SpawnLocation;
	PlayerMovingState m_PlayerMovingState = PlayerMovingState::Idle;
	float m_Speed = 100;
	sen::Vector2f m_Direction;

	Level* m_pLevel;

	bool m_IsAngry;
	bool m_IsDead;

	int m_Lives;
	float m_TimeAngry;

	int m_PlayerIdx;

	//Helper Functions
	void UpdateInput();
	virtual void InitInput();
	virtual void UpdateAngry(float elapsedSec);
	void UpdateMovement();
};

