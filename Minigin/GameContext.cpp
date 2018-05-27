#include "MiniginPCH.h"
#include "GameContext.h"


GameContext::GameContext()
{
	m_pGameTime = new GameTime();
}


GameContext::~GameContext()
{
	delete m_pGameTime;
}

GameTime* GameContext::GetGameTime()
{
	return m_pGameTime;
}
