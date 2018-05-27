#include "MiniginPCH.h"
#include "Ghostman.h"
#include "TextureComponent.h"
#include "InputAction.h"
#include "InputManager.h"
#include "RigidBodyComponent.h"


Ghostman::Ghostman()
{
}


Ghostman::~Ghostman()
{
}

void Ghostman::Create(Level* level, int playerIdx, Pacman* pacman, sen::Vector2f spawnLoc)
{
	Pacman::Create(level, playerIdx, spawnLoc);

	GetComponent<TextureComponent>()->LoadTexture("Ghostman.png");
	m_pPacman = pacman;
}

void Ghostman::Update(GameContext* gameContext)
{
	Pacman::Update(gameContext);

	UpdatePlayerCollision();
}


void Ghostman::InitInput()
{
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Left), 1, InputState::Down, 'A'));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Right), 1, InputState::Down, 'D'));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Up), 1, InputState::Down, 'W'));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Down), 1, InputState::Down, 'S'));
}

void Ghostman::UpdatePlayerCollision()
{
	auto playerRigid = m_pPacman->GetComponent<RigidBodyComponent>();
	auto thisRigid = this->GetComponent<RigidBodyComponent>();

	if (thisRigid->IsOverlapping(playerRigid))
	{
		if (m_pPacman->IsAngry())
		{
			Die();
		}
		else
		{
			m_pPacman->Die();
		}
	}
}
