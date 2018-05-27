#include "MiniginPCH.h"
#include "WinningScene.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "TransformComponent.h"


WinningScene::WinningScene() : BaseScene("WinningScene")
{
}


WinningScene::~WinningScene()
{
}

void WinningScene::Initialize(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	//Tile
	m_pWinningText = new dae::GameObject();
	auto textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 50);
	textComp->SetText("You Won");
	m_pWinningText->AddComponent(textComp);
	auto renderComp = new RenderComponent(false, false, true);
	m_pWinningText->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	m_pWinningText->GetTransform()->SetPosition(225, 200);
	AddChild(m_pWinningText);

}