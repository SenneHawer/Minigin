#pragma once
#include "BaseScene.h"
#include "Vector2f.h"
#include "Level.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GhostManager.h"

class PacmanScene final : public BaseScene
{
public:
	PacmanScene();
	~PacmanScene();

	void Initialize(GameContext* gameContext) override;
	void Update(GameContext* gameContext) override;

private:
	//GameObjects
	Pacman* m_pPacman = nullptr;
	dae::GameObject* m_pScoreText = nullptr;
	dae::GameObject* m_pLivesText = nullptr;
	dae::GameObject* m_pBackGround = nullptr;
	//Ghost* m_pGhost = nullptr;
	GhostManager* m_pGhostManager = nullptr;

	//Level
	Level* m_pLevel = nullptr;
};