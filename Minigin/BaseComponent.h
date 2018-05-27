#pragma once
namespace dae
{
	class GameObject;
}

class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent();

	virtual void Initialize() = 0;
	virtual void Update() = 0;

	dae::GameObject* GetGameObject() const { return m_pGameObject; }

	friend class dae::GameObject;

	//Rule of 5
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

protected:
	dae::GameObject* m_pGameObject;

private:
	

};

