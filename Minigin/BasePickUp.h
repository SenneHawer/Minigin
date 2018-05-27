#pragma once
#include "GameObject.h"

class BasePickUp : public dae::GameObject
{
public:
	BasePickUp(const std::string& assetFile);
	virtual ~BasePickUp();

	void Update(GameContext* gameContext) override;
	virtual bool IsOverlapping(GameObject* player);

private:


};

