#include "MiniginPCH.h"
#include "LevelTestScene.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "InputAction.h"
#include "InputManager.h"
#include "GameContext.h"
#include "TransformComponent.h"


LevelTestScene::LevelTestScene() : BaseScene("LevelTestScene")
{
}


LevelTestScene::~LevelTestScene()
{
}

void LevelTestScene::Initialize(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	//Wall1
	m_pWall1 = new dae::GameObject();
	auto rigidbody = new RigidBodyComponent(100.0f, 100.0f, 0);
	auto renderComp = new RenderComponent(true, false);
	m_pWall1->AddComponent(rigidbody);
	m_pWall1->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);

	AddChild(m_pWall1);
	m_pWall1->GetTransform()->Translate(200, 100);

	////Wall2
	//m_pWall2 = new dae::GameObject();
	//rigidbody = new RigidBodyComponent(100.0f, 100.0f, 0);
	//renderComp = new RenderComponent(true, false);
	//m_pWall2->AddComponent(rigidbody);
	//m_pWall2->AddComponent(renderComp);
	//dae::Renderer::GetInstance().NotifyRender(renderComp);

	//AddChild(m_pWall2);
	//m_pWall2->GetTransform()->Translate(0, 300.0f);

	////Wall3
	//m_pWall3 = new dae::GameObject();
	//rigidbody = new RigidBodyComponent(100.0f, 400.0f, 0);
	//renderComp = new RenderComponent(true, false);
	//m_pWall3->AddComponent(rigidbody);
	//m_pWall3->AddComponent(renderComp);
	//dae::Renderer::GetInstance().NotifyRender(renderComp);

	//AddChild(m_pWall3);
	//m_pWall3->GetTransform()->Translate(600, 0.0f);

	//Player
	m_pPlayer = new dae::GameObject();
	rigidbody = new RigidBodyComponent(100.0f, 100.0f, 100.0f);
	renderComp = new RenderComponent(true, false);

	m_pPlayer->AddComponent(rigidbody);
	m_pPlayer->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	AddChild(m_pPlayer);
	m_pPlayer->GetTransform()->Translate(0, 150.0f);

	//Input
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(MoveState::Left), 0, InputState::Down, VK_LEFT));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(MoveState::Right), 0, InputState::Down, VK_RIGHT));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(MoveState::Up), 0, InputState::Down, VK_UP));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(MoveState::Down), 0, InputState::Down, VK_DOWN));
}

void LevelTestScene::Update(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	float elapsedSec = gameContext->GetGameTime()->GetElapsedSec();

	UpdateInput(gameContext);
	UpdateCollisions(m_pWall1);
	//UpdateCollisions(m_pWall2);
	//UpdateCollisions(m_pWall3);

	m_pPlayer->GetTransform()->Move(m_Velocity * m_Speed, elapsedSec);

}


//Helper Functions
void LevelTestScene::UpdateInput(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	if (dae::InputManager::GetInstance().IsActionTriggered(0, int(MoveState::Left)))
	{
		m_Velocity.x = -1;
	}
	else if (dae::InputManager::GetInstance().IsActionTriggered(0, int(MoveState::Right)))
	{
		m_Velocity.x = 1;
	}
	else
	{
		m_Velocity.x = 0;
	}

	if (dae::InputManager::GetInstance().IsActionTriggered(0, int(MoveState::Up)))
	{
		m_Velocity.y = -1;
	}
	else if (dae::InputManager::GetInstance().IsActionTriggered(0, int(MoveState::Down)))
	{
		m_Velocity.y = 1;
	}
	else
	{
		m_Velocity.y = 0;
	}
}
void LevelTestScene::UpdateCollisions(dae::GameObject* otherObj)
{
	auto otherComp = otherObj->GetComponent<RigidBodyComponent>();

	if (m_pPlayer->GetComponent<RigidBodyComponent>()->IsUpOverlapping(otherComp->GetPosition(), otherComp->GetWidth(), otherComp->GetHeight()))
	{
		otherObj->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
		if (m_Velocity.y < 0) m_Velocity.y = 0;
	}
	else if (m_pPlayer->GetComponent<RigidBodyComponent>()->IsDownOverlapping(otherComp->GetPosition(), otherComp->GetWidth(), otherComp->GetHeight()))
	{
		otherObj->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
		if (m_Velocity.y > 0) m_Velocity.y = 0;
	}
	else if (m_pPlayer->GetComponent<RigidBodyComponent>()->IsLeftOverlapping(otherComp->GetPosition(), otherComp->GetWidth(), otherComp->GetHeight()))
	{
		otherObj->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
		if (m_Velocity.x < 0) m_Velocity.x = 0;
	}
	else if (m_pPlayer->GetComponent<RigidBodyComponent>()->IsRightOverlapping(otherComp->GetPosition(), otherComp->GetWidth(), otherComp->GetHeight()))
	{
		otherObj->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
		if (m_Velocity.x > 0) m_Velocity.x = 0;
	}
	else
	{
		otherObj->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(255, 255, 255));
	}
}
