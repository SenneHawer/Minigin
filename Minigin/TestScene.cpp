#include "MiniginPCH.h"
#include "TestScene.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "Vector2f.h"
#include "TransformComponent.h"
#include "GameContext.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "InputManager.h"
#include "RigidBodyComponent.h"
#include "TextComponent.h"


TestScene::TestScene()
	:BaseScene("TestScene")
{
}


TestScene::~TestScene()
{
}

void TestScene::Initialize(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	//obj1
	m_pTestObj = new dae::GameObject();

	auto textureComp = new TextureComponent();
	textureComp->LoadTexture("background.jpg");
	m_pTestObj->AddComponent(textureComp);

	auto renderComp = new RenderComponent(false, true);
	m_pTestObj->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);

	AddChild(m_pTestObj);

	//obj2
	m_pTestObj2 = new dae::GameObject();

	textureComp = new TextureComponent();
	textureComp->LoadTexture("logo.png");
	m_pTestObj2->AddComponent(textureComp);

	RigidBodyComponent* rigidbody = new RigidBodyComponent(210.0f, 100.0f, 50.0f);
	m_pTestObj2->AddComponent(rigidbody);

	renderComp = new RenderComponent(true, true);
	m_pTestObj2->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);

	m_pTestObj2->GetTransform()->Translate(0, 100.0f);

	AddChild(m_pTestObj2);




	//Input
	dae::InputManager::GetInstance().AddInputAction(InputAction{ 0, 0, InputState::Release, 'K' });

}

void TestScene::Update(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	float elapsedSec = gameContext->GetGameTime()->GetElapsedSec();
	//m_pTestObj->GetComponent<TransformComponent>()->Move(sen::Vector2f{ 100.0f,-100.0f }, elapsedSec);

	m_pTestObj2->GetTransform()->Move(m_Velocity, elapsedSec);



	if (dae::InputManager::GetInstance().IsActionTriggered(0, 0))
	{
		m_Velocity = -m_Velocity;
	}
}