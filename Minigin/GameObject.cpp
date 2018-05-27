#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

dae::GameObject::GameObject()
{
	//Add TransformComponent by default
	m_pTransformComp = new TransformComponent();
	AddComponent(m_pTransformComp);
}

dae::GameObject::~GameObject()
{
	//Delete Components
	for (BaseComponent* pComponent : m_pComponents)
	{
		if (pComponent != nullptr)
		{
			delete pComponent;
			pComponent = nullptr;
		}
	}
	for (dae::GameObject* pObj : m_pChildObjects)
	{
		delete pObj;
		pObj = nullptr;
	}
}

void dae::GameObject::Update(GameContext* gameContext)
{
	for (auto pComp : m_pComponents)
	{
		pComp->Update();
	}
	for (auto pObj : m_pChildObjects)
	{
		pObj->Update(gameContext);
	}
}

//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	UNREFERENCED_PARAMETER(filename);
//	//mTexture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::AddComponent(BaseComponent* pComponent)
{
	UNREFERENCED_PARAMETER(pComponent);
	//Check if the component already exists
	for (auto check : m_pComponents)
	{
		if (check == pComponent)
		{
			std::cout << "GameObject::AddComponent: Component already exists" << std::endl;
			return;
		}
	}
	//Push back component
	m_pComponents.push_back(pComponent);
	//Set the gameobject to this
	pComponent->m_pGameObject = this;
}

void dae::GameObject::AddChild(dae::GameObject* gameObj)
{
	m_pChildObjects.push_back(gameObj);
}

void dae::GameObject::RemoveChild(dae::GameObject* gameObj)
{
	auto iterator = std::find(m_pChildObjects.begin(), m_pChildObjects.end(), gameObj);

	auto render = gameObj->GetComponent<RenderComponent>();
	dae::Renderer::GetInstance().DeNotifyRenderer(render);

	delete gameObj;
	gameObj = nullptr;

	m_pChildObjects.erase(iterator);
}


TransformComponent* dae::GameObject::GetTransform()
{
	return m_pTransformComp;
}
