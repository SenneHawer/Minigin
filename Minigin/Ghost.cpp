#include "MiniginPCH.h"
#include "Ghost.h"
#include "RigidBodyComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Level.h"
#include "TransformComponent.h"
#include "Pacman.h"
#include "TextureComponent.h"
#include "Ghostman.h"

Ghost::Ghost(Level* level, std::vector<Pacman*> pPacmans, sen::Vector2f spawnLocation)
	:m_Speed(100.0f)
	,m_Direction(0,-1)
	,m_PrevDir(0,0)
	,m_IsSleeping(true)
	,m_SpawnLocation(spawnLocation)
	,m_LoadedNormalTexture(true)
	,m_LoadedScaredTexture(false)
	,m_AngryPacmans(false)
{
	auto textureComp = new TextureComponent();
	textureComp->LoadTexture("Ghost.png");
	textureComp->SetDimensions(15, 15);
	AddComponent(textureComp);

	auto rigidbody = new RigidBodyComponent(15, 15, 0);
	AddComponent(rigidbody);

	auto renderComp = new RenderComponent(false, true, false);
	AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);

	m_pLevel = level;
	//m_pPacman = pacman;
	m_pPacmans = pPacmans;

	GetTransform()->SetPosition(spawnLocation.x, spawnLocation.y);
}


Ghost::~Ghost()
{
}

void Ghost::Update(GameContext* gameContext)
{
	dae::GameObject::Update(gameContext);
	auto elapsedSec = gameContext->GetGameTime()->GetElapsedSec();
	UpdateScared();

	if (m_IsSleeping)
	{
		m_Direction = { 0,0 };

		m_TimeAsleep += elapsedSec;
		if (m_TimeAsleep >= 5.0f)
		{
			m_IsSleeping = false;
			m_TimeAsleep = 0;
			m_Direction.y = -1;
		}
		return;
	}

	m_pLevel->UpdateCollision(this, m_Direction);
	for (auto pacman : m_pPacmans)
	{
		auto ghost = dynamic_cast<Ghostman*>(pacman);
		if (ghost != NULL) continue;

		if (pacman->GetComponent<RigidBodyComponent>()->IsOverlapping(GetComponent<RigidBodyComponent>()))
		{
			if (!m_AngryPacmans)
				pacman->Die();
			else
			{
				Die();
			}
		}
	}

	if (m_Direction.x == 0 && m_Direction.y == 0) //Not Moving
	{
		ChooseDirection();
	}

	sen::Vector2f velocity = m_Direction * m_Speed;
	this->GetTransform()->Move(velocity, elapsedSec);
	//m_PrevDir = m_Direction;
}

void Ghost::ChooseDirection()
{
	int choise = std::rand() % 4;

	switch(choise)
	{
	case 1:
		GoUp();
		break;
	case 2:
		GoDown();
		break;
	case 3:
		GoLeft();
		break;
	case 4:
		GoRight();
		break;
	}
}

void Ghost::GoUp()
{
	m_Direction.y = -1;
	m_Direction.x = 0;
}

void Ghost::GoDown()
{
	m_Direction.y = 1;
	m_Direction.x = 0;
}

void Ghost::GoLeft()
{
	m_Direction.y = 0;
	m_Direction.x = -1;
}

void Ghost::GoRight()
{
	m_Direction.y = 0;
	m_Direction.x = 1;
}

void Ghost::Die()
{
	m_IsSleeping = true;
	GetTransform()->SetPosition(m_SpawnLocation.x, m_SpawnLocation.y);
}

void Ghost::UpdateScared()
{
	m_AngryPacmans = false;	
	for (auto pacman : m_pPacmans)
	{
		if (m_AngryPacmans == true) break; //If 1 is angry, they all are. So the loop can be stopped

		if (pacman->IsAngry())
		{
			m_AngryPacmans = true;
		}
	}
	
	//Update Texture
	if (m_AngryPacmans)
	{
		if (!m_LoadedScaredTexture)
		{
			m_LoadedNormalTexture = false;
			GetComponent<TextureComponent>()->LoadTexture("GhostScared.png");
			m_LoadedScaredTexture = true;
		}
	}
	else
	{
		if (!m_LoadedNormalTexture)
		{
			m_LoadedScaredTexture = false;
			GetComponent<TextureComponent>()->LoadTexture("Ghost.png");
			m_LoadedNormalTexture = true;
		}
	}
	//for (auto pacman : m_pPacmans)
	//{
	//	if (pacman->IsAngry())
	//	{
	//		if (!m_LoadedScaredTexture)
	//		{
	//			m_LoadedNormalTexture = false;
	//			GetComponent<TextureComponent>()->LoadTexture("GhostScared.png");
	//			m_LoadedScaredTexture = true;
	//			m_AngryPacmans = true;
	//		}
	//	}
	//	else
	//	{
	//		if (!m_LoadedNormalTexture)
	//		{
	//			m_LoadedScaredTexture = false;
	//			GetComponent<TextureComponent>()->LoadTexture("Ghost.png");
	//			m_LoadedNormalTexture = true;
	//			m_AngryPacmans = false;
	//		}
	//	}
	//}
}
