#include "MiniginPCH.h"
#include "GhostManager.h"
#include "TransformComponent.h"

GhostManager::GhostManager()
{
}


GhostManager::~GhostManager()
{
}

void GhostManager::Update(GameContext* gameContext)
{
	dae::GameObject::Update(gameContext);

}

void GhostManager::CreateGhost(Level* pLevel, std::vector<Pacman*> pPacmans, sen::Vector2f position)
{
	Ghost* pGhost = new Ghost(pLevel, pPacmans, position);
	//pGhost->GetTransform()->SetPosition(position.x, position.y);
	AddChild(pGhost);
}
