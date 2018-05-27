#include "MiniginPCH.h"
#include "GameOverScene.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "TransformComponent.h"


GameOverScene::GameOverScene() : BaseScene("GameOverScene")
{
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	//Tile
	m_pGameOverText = new dae::GameObject();
	auto textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 50);
	textComp->SetText("GAME OVER");
	m_pGameOverText->AddComponent(textComp);
	auto renderComp = new RenderComponent(false, false, true);
	m_pGameOverText->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	m_pGameOverText->GetTransform()->SetPosition(200, 200);
	AddChild(m_pGameOverText);
}

void GameOverScene::Update(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

}