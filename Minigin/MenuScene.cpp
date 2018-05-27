#include "MiniginPCH.h"
#include "MenuScene.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "InputAction.h"
#include "InputManager.h"
#include "SceneManager.h"


MenuScene::MenuScene() : BaseScene("MenuScene")
{
}


MenuScene::~MenuScene()
{
}

void MenuScene::Initialize(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	//Tile
	m_pTitleText = new dae::GameObject();
	auto textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 50);
	textComp->SetText("PACMAN");
	m_pTitleText->AddComponent(textComp);
	auto renderComp = new RenderComponent(false, false, true);
	m_pTitleText->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	m_pTitleText->GetTransform()->SetPosition(225, 200);
	AddChild(m_pTitleText);

	//Creator
	m_pCreatorText = new dae::GameObject();
	textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 26);
	textComp->SetText("Senne Hawer - 2DAE1 - 2017-2018");
	m_pCreatorText->AddComponent(textComp);
	renderComp = new RenderComponent(false, false, true);
	m_pCreatorText->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	m_pCreatorText->GetTransform()->SetPosition(0, 0);
	AddChild(m_pCreatorText);

	//Instruction
	m_pInstructionText1 = new dae::GameObject();
	textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 26);
	textComp->SetText("Press 1/A for Singleplayer");
	m_pInstructionText1->AddComponent(textComp);
	renderComp = new RenderComponent(false, false, true);
	m_pInstructionText1->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	m_pInstructionText1->GetTransform()->SetPosition(100, 300);
	AddChild(m_pInstructionText1);

	m_pInstructionText2 = new dae::GameObject();
	textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 26);
	textComp->SetText("Press 2/B for 2 Pacmans");
	m_pInstructionText2->AddComponent(textComp);
	renderComp = new RenderComponent(false, false, true);
	m_pInstructionText2->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	m_pInstructionText2->GetTransform()->SetPosition(100, 340);
	AddChild(m_pInstructionText2);

	m_pInstructionText3 = new dae::GameObject();
	textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 26);
	textComp->SetText("Press 3/X for 1 Pacman and 1 Ghost");
	m_pInstructionText3->AddComponent(textComp);
	renderComp = new RenderComponent(false, false, true);
	m_pInstructionText3->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	m_pInstructionText3->GetTransform()->SetPosition(100, 380);
	AddChild(m_pInstructionText3);

	dae::InputManager::GetInstance().AddInputAction(InputAction(int(SceneInput::Singleplayer), 0, InputState::Pressed, VK_NUMPAD1, -1, XINPUT_GAMEPAD_A));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(SceneInput::MultiplayerPacman), 0, InputState::Pressed, VK_NUMPAD2, -1, XINPUT_GAMEPAD_B));
	dae::InputManager::GetInstance().AddInputAction(InputAction(int(SceneInput::MultiplayerGhost), 0, InputState::Pressed, VK_NUMPAD3, -1, XINPUT_GAMEPAD_X));
}

void MenuScene::Update(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	if (dae::InputManager::GetInstance().IsActionTriggered(0, int(SceneInput::Singleplayer)))
	{
		dae::SceneManager::GetInstance().ActivateSceneByName("PacmanScene");
	}
	if (dae::InputManager::GetInstance().IsActionTriggered(0, int(SceneInput::MultiplayerPacman)))
	{
		dae::SceneManager::GetInstance().ActivateSceneByName("MultiplayerScene");
	}
	if (dae::InputManager::GetInstance().IsActionTriggered(0, int(SceneInput::MultiplayerGhost)))
	{
		dae::SceneManager::GetInstance().ActivateSceneByName("MultiplayerGhostScene");
	}

}
