#pragma once
#include "GameObject.h"
#include "Ghost.h"

class GhostManager final : public dae::GameObject
{
public:
	GhostManager();
	virtual ~GhostManager();

	virtual void Update(GameContext* gameContext) override;
	void CreateGhost(Level* pLevel, std::vector<Pacman*> pPacmans, sen::Vector2f position);

private:

};

