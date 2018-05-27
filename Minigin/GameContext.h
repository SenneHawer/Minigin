#pragma once
#include "GameTime.h"

class GameContext
{
public:
	GameContext();
	~GameContext();

	GameTime* GetGameTime();

private:
	GameTime* m_pGameTime = nullptr;
};

