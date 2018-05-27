#include "MiniginPCH.h"
#include "BaseScene.h"
#include "GameContext.h"
#include "GameObject.h"
#include "InputManager.h"


BaseScene::BaseScene(std::string sceneName)
	:m_SceneName(sceneName)
{
}


BaseScene::~BaseScene()
{
	delete m_pGameContext;

	for (auto pChild : m_pChildObjects)
	{
			delete pChild;
	}
}

//PUBLIC
bool BaseScene::AddChild(dae::GameObject* gameObj)
{
	UNREFERENCED_PARAMETER(gameObj);
	m_pChildObjects.push_back(gameObj);

	return true;
}

void BaseScene::RootInitialize()
{
	dae::InputManager::GetInstance().ClearInputActions();

	//create Context
	m_pGameContext = new GameContext();
	m_pGameContext->GetGameTime()->Reset();
	m_pGameContext->GetGameTime()->Start();

	//User Init
	this->Initialize(m_pGameContext);
}


void BaseScene::RootUpdate()
{
	for (auto obj : m_pChildObjects)
	{
		obj->Update(m_pGameContext);
	}

	//GameTimer Update
	m_pGameContext->GetGameTime()->Update();

	//User Update
	this->Update(m_pGameContext);
}

std::string BaseScene::GetName()
{
	return m_SceneName;
}
