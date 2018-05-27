#pragma once
#include <memory>

#include "Transform.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include <vector>
#include "GameContext.h"

class TransformComponent;
class RenderComponent;

namespace dae
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Update(GameContext* gameContext);

		//void SetTexture(const std::string& filename);
		void AddComponent(BaseComponent* pComponent);
		void AddChild(dae::GameObject* gameObj);
		void RemoveChild(dae::GameObject* gameObj);
		//void RemoveComponent();

		TransformComponent* GetTransform();
#pragma region
		template<class T>T* GetComponent()
		{
			const type_info& askedType = typeid(T);

			for (BaseComponent* pComp : m_pComponents)
			{
				if (pComp && typeid(*pComp) == askedType)
				{
					return static_cast<T*>(pComp);
				}
			}

			return nullptr;
		}
#pragma endregion Template Functions

		//Rule of 5
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		//std::shared_ptr<Texture2D> mTexture;

		TransformComponent* m_pTransformComp = nullptr;
		std::vector<BaseComponent*> m_pComponents;

		std::vector<dae::GameObject*> m_pChildObjects;
	};
}
