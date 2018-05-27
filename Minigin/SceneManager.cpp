#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "BaseScene.h"
#include "Renderer.h"
#include <algorithm>


void dae::SceneManager::Update()
{
	if (m_pActiceScene)
		m_pActiceScene->RootUpdate();
}

void dae::SceneManager::ActivateScene(std::shared_ptr<BaseScene> scene)
{
	m_pActiceScene = scene;

	if (m_pActiceScene)
		m_pActiceScene->RootInitialize();
}

void dae::SceneManager::ActivateNextScene()
{
	auto it = std::find(m_pScenes.begin(), m_pScenes.end(), m_pActiceScene);
	auto index = it - m_pScenes.begin();
	++index;
	if (unsigned int(index) < m_pScenes.size())
	{
		m_pActiceScene = m_pScenes.at(index);
		dae::Renderer::GetInstance().EmptyRenderer();
		m_pActiceScene->RootInitialize();
	}
	else
	{
		m_pActiceScene = m_pScenes.at(0);
		dae::Renderer::GetInstance().EmptyRenderer();
		m_pActiceScene->RootInitialize();
	}
}


void dae::SceneManager::AddScene(std::shared_ptr<BaseScene> scene)
{
	m_pScenes.push_back(scene);
	if (!m_pActiceScene)
	{
		m_pActiceScene = scene;
		m_pActiceScene->RootInitialize();
	}
}

void dae::SceneManager::ActivateSceneByName(std::string sceneName)
{
	auto it = std::find_if(m_pScenes.begin(), m_pScenes.end(), [&](auto scene)
	{
		return scene->GetName() == sceneName;
	});

	m_pActiceScene = *it;
	dae::Renderer::GetInstance().EmptyRenderer();
	m_pActiceScene->RootInitialize();
}
