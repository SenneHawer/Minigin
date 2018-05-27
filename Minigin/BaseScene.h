#pragma once
#include <vector>
class GameContext;

namespace dae {
	class GameObject;
}

class BaseScene
{
public:
	BaseScene(std::string sceneName);
	~BaseScene();

	bool AddChild(dae::GameObject* gameObj);

	void RootInitialize();
	void RootUpdate();
	std::string GetName();

protected:
	virtual void Initialize(GameContext* gameContext) = 0;
	virtual void Update(GameContext* gameContext) = 0;

private:

	//Functions


	//Variables
	std::vector<dae::GameObject*> m_pChildObjects;
	std::string m_SceneName;

	GameContext* m_pGameContext = nullptr;
};

