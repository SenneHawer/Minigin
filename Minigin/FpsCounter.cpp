#include "MiniginPCH.h"
#include "FpsCounter.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"


FpsCounter::FpsCounter()
{
	auto textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 36);
	AddComponent(textComp);
	auto renderComp = new RenderComponent(false, false, true);
	AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
}


FpsCounter::~FpsCounter()
{
}

void FpsCounter::Update(GameContext* gameContext)
{
	dae::GameObject::Update(gameContext);

	std::stringstream ss;
	ss << gameContext->GetGameTime()->GetFPS();

	GetComponent<TextComponent>()->SetText(ss.str());
}
