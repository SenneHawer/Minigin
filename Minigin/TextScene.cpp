#include "MiniginPCH.h"
#include "TextScene.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"


TextScene::TextScene() : BaseScene("TextScene")
{
}


TextScene::~TextScene()
{
}

void TextScene::Initialize(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	//Text
	m_pText = new dae::GameObject();
	auto textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 36);
	textComp->SetText("BOOM");
	m_pText->AddComponent(textComp);

	auto renderComp = new RenderComponent(false, false, true);
	m_pText->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);

	m_pText->GetTransform()->SetPosition(280, 200);
	AddChild(m_pText);
}

void TextScene::Update(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
}

