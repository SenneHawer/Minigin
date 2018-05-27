#include "MiniginPCH.h"
#include "Pacman.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "Renderer.h"
#include "InputAction.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "Level.h"


Pacman::Pacman()
	:GameObject()
	,m_IsAngry(false)
	,m_IsDead(false)
	,m_SpawnLocation(26, 279)
	,m_Lives(3)
{

}


Pacman::~Pacman()
{
}

void Pacman::Create(Level* level, int playerIdx, sen::Vector2f spawnLoc)
{
	m_PlayerIdx = playerIdx;
	m_SpawnLocation = spawnLoc;

	//COMPONENTS
	//Texture Component
	auto textureComp = new TextureComponent();
	textureComp->LoadTexture("Pacman.png");
	textureComp->SetDimensions(15, 15);
	this->AddComponent(textureComp);

	//RigidBody Component
	auto rigidbody = new RigidBodyComponent(15, 15, 0);
	this->AddComponent(rigidbody);

	//Render Component
	auto renderComp = new RenderComponent(false, true);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	this->AddComponent(renderComp);

	//INPUT
	InitInput();

	m_pLevel = level;

	GetTransform()->SetPosition(m_SpawnLocation.x, m_SpawnLocation.y);
}


void Pacman::Update(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	dae::GameObject::Update(gameContext);

	float elapsedSec = gameContext->GetGameTime()->GetElapsedSec();

	UpdateAngry(elapsedSec);

	UpdateInput();

	UpdateMovement();

	m_pLevel->UpdateCollision(this, m_Direction);

	sen::Vector2f velocity = m_Direction * m_Speed;
	GetTransform()->Move(velocity, elapsedSec);
}

sen::Vector2f& Pacman::GetDirectionRef()
{
	return m_Direction;
}

bool Pacman::IsAngry()
{
	return m_IsAngry;
}

bool Pacman::IsDead()
{
	return m_IsDead;
}

void Pacman::Die()
{
	--m_Lives;
	m_PlayerMovingState = PlayerMovingState::Idle;
	GetTransform()->SetPosition(m_SpawnLocation.x, m_SpawnLocation.y);

	if(m_Lives == 0)
	{
		m_IsDead = true;
	}
}

void Pacman::MakeAngry()
{
	m_IsAngry = true;
}


int Pacman::GetLives()
{
	return m_Lives;
}


void Pacman::UpdateInput()
{
	//INPUT
	if (dae::InputManager::GetInstance().IsActionTriggered(m_PlayerIdx, int(PlayerMovingState::Left)))
	{
		m_PlayerMovingState = PlayerMovingState::Left;
	}
	else if (dae::InputManager::GetInstance().IsActionTriggered(m_PlayerIdx, int(PlayerMovingState::Right)))
	{
		m_PlayerMovingState = PlayerMovingState::Right;
	}

	else if (dae::InputManager::GetInstance().IsActionTriggered(m_PlayerIdx, int(PlayerMovingState::Up)))
	{
		m_PlayerMovingState = PlayerMovingState::Up;
	}
	else if (dae::InputManager::GetInstance().IsActionTriggered(m_PlayerIdx, int(PlayerMovingState::Down)))
	{
		m_PlayerMovingState = PlayerMovingState::Down;
	}
}


void Pacman::InitInput()
{
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Left), m_PlayerIdx, InputState::Down, VK_LEFT, -1, XINPUT_GAMEPAD_DPAD_LEFT));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Right), m_PlayerIdx, InputState::Down, VK_RIGHT, -1, XINPUT_GAMEPAD_DPAD_RIGHT));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Up), m_PlayerIdx, InputState::Down, VK_UP, -1, XINPUT_GAMEPAD_DPAD_UP));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(PlayerMovingState::Down), m_PlayerIdx, InputState::Down, VK_DOWN, -1, XINPUT_GAMEPAD_DPAD_DOWN));
}

void Pacman::UpdateAngry(float elapsedSec)
{
	if (m_IsAngry)
	{
		m_TimeAngry += elapsedSec;

		if (m_TimeAngry >= 10.0f)
		{
			m_IsAngry = false;
			m_TimeAngry = 0;
		}
	}
}

void Pacman::UpdateMovement()
{
	//INPUT
	if (m_PlayerMovingState == PlayerMovingState::Left)
	{
		m_Direction.x = -1;
		//m_Direction.y = 0.5f;
	}
	else if (m_PlayerMovingState == PlayerMovingState::Right)
	{
		m_Direction.x = 1;
		//m_Direction.y = 0.5f;
	}

	else if (m_PlayerMovingState == PlayerMovingState::Up)
	{
		m_Direction.y = -1;
		//m_Direction.x = 0.5f;
	}
	else if (m_PlayerMovingState == PlayerMovingState::Down)
	{
		m_Direction.y = 1;
		//m_Direction.x = 0.5f;
	}
	else if (m_PlayerMovingState == PlayerMovingState::Idle)
	{
		m_Direction.x = 0;
		m_Direction.y = 0;
	}
}

