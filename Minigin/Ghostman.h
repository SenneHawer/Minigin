#pragma once
#include "Pacman.h"
class Ghostman final : public Pacman
{
public:
	Ghostman();
	virtual ~Ghostman();

	void Create(Level* level, int playerIdx, Pacman* pacman, sen::Vector2f spawnLoc);
	void Update(GameContext* gameContext) override;

private:
	virtual void InitInput() override;
	virtual void UpdateAngry(float elapsedSec) override { UNREFERENCED_PARAMETER(elapsedSec); }

	void UpdatePlayerCollision();

	Pacman* m_pPacman;
};

