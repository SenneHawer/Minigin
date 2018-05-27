#pragma once
#include "Singleton.h"
#include "BaseScene.h"

namespace dae
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void ActivateScene(std::shared_ptr<BaseScene> scene);
		void AddScene(std::shared_ptr<BaseScene> scene);
		void ActivateNextScene();
		void ActivateSceneByName(std::string sceneName);

		void Update(float deltaTime);
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;

		std::shared_ptr<BaseScene> m_pActiceScene;
		std::vector<std::shared_ptr<BaseScene>> m_pScenes;

	};

}
