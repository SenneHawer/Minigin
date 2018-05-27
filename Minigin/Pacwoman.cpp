#include "MiniginPCH.h"
#include "Pacwoman.h"
#include "TextureComponent.h"
#include "InputManager.h"


Pacwoman::Pacwoman()
{
}


Pacwoman::~Pacwoman()
{
}

void Pacwoman::Create(Level* level, int playerIdx, sen::Vector2f spawnLoc)
{
	Pacman::Create(level, playerIdx, spawnLoc);

	GetComponent<TextureComponent>()->LoadTexture("Pacwoman.png");
}


void Pacwoman::InitInput()
{
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Left), 1, InputState::Down, 'A'));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Right), 1, InputState::Down, 'D'));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Up), 1, InputState::Down, 'W'));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Down), 1, InputState::Down, 'S'));
}
