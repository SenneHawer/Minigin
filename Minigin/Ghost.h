#pragma once
#include "GameObject.h"
#include "Vector2f.h"

class Pacman;
class Level;

class Ghost final : public dae::GameObject
{
public:
	Ghost(Level* level, std::vector<Pacman*> pPacmans, sen::Vector2f spawnLocation);
	~Ghost();

	void Update(GameContext* gameContext) override;

private:
	void ChooseDirection();
	void Sleep(float elapsedSec);
	void Die();
	void UpdateScared();

	//Choises
	void GoUp();
	void GoDown();
	void GoLeft();
	void GoRight();

	Level* m_pLevel = nullptr;
	//Pacman* m_pPacman = nullptr;
	std::vector<Pacman*> m_pPacmans;

	sen::Vector2f m_SpawnLocation;
	sen::Vector2f m_Direction;
	sen::Vector2f m_PrevDir;
	float m_Speed;

	bool m_IsSleeping;
	float m_TimeAsleep;
	bool m_AngryPacmans;

	bool m_LoadedScaredTexture;
	bool m_LoadedNormalTexture;
};

