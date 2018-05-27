#pragma once
#include "Pacman.h"

class Pacwoman final : public Pacman
{
public:
	Pacwoman();
	virtual ~Pacwoman();

	virtual void Create(Level* level, int playerIdx, sen::Vector2f spawnLoc) override;

private:
	virtual void InitInput() override;
};

