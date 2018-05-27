#include "MiniginPCH.h"
#include "MultiplayerGhostScene.h"
#include "RigidBodyComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "InputManager.h"
#include "GameContext.h"
#include "TextComponent.h"
#include "SceneManager.h"
#include "FpsCounter.h"
#include "Pacwoman.h"


MultiplayerGhostScene::MultiplayerGhostScene()
	:BaseScene("MultiplayerGhostScene")
{
}


MultiplayerGhostScene::~MultiplayerGhostScene()
{
}

void MultiplayerGhostScene::Initialize(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	//BackGround
	m_pBackGround = new dae::GameObject();
	auto textureComp = new TextureComponent();
	textureComp->LoadTexture("background.jpg");
	m_pBackGround->AddComponent(textureComp);
	auto renderComp = new RenderComponent(false, false , false);
	m_pBackGround->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	AddChild(m_pBackGround);
	
	//Level
	m_pLevel = new Level();
	m_pLevel->CreateLevel("../Data/LevelSeed.txt");
	AddChild(m_pLevel);

	//Pacman
	m_pPacman = new Pacman();
	m_pPacman->Create(m_pLevel, 0, {26, 279});
	AddChild(m_pPacman);

	//Ghostman
	m_pGhostman = new Ghostman();
	m_pGhostman->Create(m_pLevel, 1, m_pPacman, { 598, 279 });
	AddChild(m_pGhostman);

	//Ghost
	m_pGhostManager = new GhostManager();
	AddChild(m_pGhostManager);
	std::vector<Pacman*> pacmans;
	pacmans.push_back(m_pPacman);
	pacmans.push_back(m_pGhostman);
	m_pGhostManager->CreateGhost(m_pLevel, pacmans, { 300, 300 });
	m_pGhostManager->CreateGhost(m_pLevel, pacmans, { 290, 280 });
	m_pGhostManager->CreateGhost(m_pLevel, pacmans, { 310, 280 });
	m_pGhostManager->CreateGhost(m_pLevel, pacmans, { 300, 280 });

	//Score
	m_pScoreText = new dae::GameObject();
	auto textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 36);
	textComp->SetText("NOT READY");
	m_pScoreText->AddComponent(textComp);
	renderComp = new RenderComponent(false, false, true);
	m_pScoreText->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	m_pScoreText->GetTransform()->SetPosition(30, 200);
	AddChild(m_pScoreText);

	//Lives
	m_pLivesText = new dae::GameObject();
	textComp = new TextComponent();
	textComp->LoadFont("Lingua.otf", 36);
	textComp->SetText("NOT READY");
	m_pLivesText->AddComponent(textComp);
	renderComp = new RenderComponent(false, false, true);
	m_pLivesText->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
	m_pLivesText->GetTransform()->SetPosition(30, 325);
	AddChild(m_pLivesText);

}

void MultiplayerGhostScene::Update(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);

	std::stringstream ss;
	ss << m_pLevel->GetScore();

	m_pScoreText->GetComponent<TextComponent>()->SetText(ss.str());

	ss.str(""); //Empty string stream
	ss << m_pPacman->GetLives();

	m_pLivesText->GetComponent<TextComponent>()->SetText(ss.str());


	//GameOver
	if (m_pPacman->IsDead())
		dae::SceneManager::GetInstance().ActivateSceneByName("GameOverScene");

	//Winner
	if (m_pLevel->GetScore() == 288)
		dae::SceneManager::GetInstance().ActivateSceneByName("WinningScene");

}