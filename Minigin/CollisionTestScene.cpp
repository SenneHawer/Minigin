#include "MiniginPCH.h"
#include "CollisionTestScene.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "GameContext.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "TransformComponent.h"

CollisionTestScene::CollisionTestScene() : BaseScene("CollisionTestScene")
{
}


CollisionTestScene::~CollisionTestScene()
{
}

void CollisionTestScene::Initialize(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	//obj1
	m_pObj1 = new dae::GameObject();
	auto rigidbody = new RigidBodyComponent(20, 20, 10);
	auto renderComp = new RenderComponent(true, false);

	m_pObj1->AddComponent(rigidbody);
	m_pObj1->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);

	m_pObj1->GetTransform()->Translate(320, 200);
	AddChild(m_pObj1);

	////obj2
	//m_pObj2 = new dae::GameObject();
	//rigidbody = new RigidBodyComponent(100.0f, 100.0f, 50.0f);
	//renderComp = new RenderComponent(true, false);

	//m_pObj2->AddComponent(rigidbody);
	//m_pObj2->AddComponent(renderComp);
	//dae::Renderer::GetInstance().NotifyRender(renderComp);

	//m_pObj2->GetTransform()->Translate(300.0f, 200.0f);

	//AddChild(m_pObj2);

	//Level
	m_pLevel = new Level();
	m_pLevel->CreateLevel("LevelSeed.txt");
	AddChild(m_pLevel);

	//Input
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(MoveState::Left), 0, InputState::Down, VK_LEFT));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(MoveState::Right), 0, InputState::Down, VK_RIGHT));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(MoveState::Up), 0, InputState::Down, VK_UP));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(MoveState::Down), 0, InputState::Down, VK_DOWN));
}

void CollisionTestScene::Update(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	float elapsedSec = gameContext->GetGameTime()->GetElapsedSec();

	if (dae::InputManager::GetInstance().IsActionTriggered(0, int(MoveState::Left)))
	{
		m_Velocity.x = -1;
	}
	else if (dae::InputManager::GetInstance().IsActionTriggered(0, int(MoveState::Right)))
	{
		m_Velocity.x = 1;
	}

	if (dae::InputManager::GetInstance().IsActionTriggered(0, int(MoveState::Up)))
	{
		m_Velocity.y = -1;
	}
	else if (dae::InputManager::GetInstance().IsActionTriggered(0, int(MoveState::Down)))
	{
		m_Velocity.y = 1;
	}

	m_pLevel->UpdateCollision(m_pObj1, m_Velocity);

	//auto otherComp = m_pObj2->GetComponent<RigidBodyComponent>();

	//if (m_pObj1->GetComponent<RigidBodyComponent>()->IsOverlapping(otherComp->GetPosition(), otherComp->GetWidth(), otherComp->GetHeight()))
	//{
	//	m_pObj2->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(255, 0, 0));

	//	//m_Velocity = {0,0};
	//	//if (!wasInside)
	//	//{
	//	//	m_Velocity = -m_Velocity*2;
	//	//	wasInside = true;
	//	//}

	//	if (m_Velocity.x > 0) m_Velocity.x = -1;
	//	else if (m_Velocity.x < 0) m_Velocity.x = 1;

	//	if (m_Velocity.y > 0) m_Velocity.y = -1;
	//	else if (m_Velocity.y < 0) m_Velocity.y = 1;


	//}
	//else
	//{
	//	m_pObj2->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(255, 255, 255));
	//	//if(wasInside)
	//	//{
	//	//	m_Velocity = -m_Velocity;
	//	//	wasInside = false;
	//	//}
	//}

	//if (m_pObj1->GetComponent<RigidBodyComponent>()->IsUpOverlapping(otherComp->GetPosition(), otherComp->GetWidth(), otherComp->GetHeight()))
	//{
	//	m_pObj2->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
	//	if (m_Velocity.y < 0) m_Velocity.y = 0;
	//}
	//if (m_pObj1->GetComponent<RigidBodyComponent>()->IsDownOverlapping(otherComp->GetPosition(), otherComp->GetWidth(), otherComp->GetHeight()))
	//{
	//	m_pObj2->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
	//	if (m_Velocity.y > 0) m_Velocity.y = 0;
	//}
	//if (m_pObj1->GetComponent<RigidBodyComponent>()->IsLeftOverlapping(otherComp->GetPosition(), otherComp->GetWidth(), otherComp->GetHeight()))
	//{
	//	m_pObj2->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
	//	if (m_Velocity.x < 0) m_Velocity.x = 0;
	//}
	//if (m_pObj1->GetComponent<RigidBodyComponent>()->IsRightOverlapping(otherComp->GetPosition(), otherComp->GetWidth(), otherComp->GetHeight()))
	//{
	//	m_pObj2->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
	//	if (m_Velocity.x > 0) m_Velocity.x = 0;
	//}

	//Move Obj
	m_pObj1->GetTransform()->Move(m_Velocity * m_Speed, elapsedSec);
}


