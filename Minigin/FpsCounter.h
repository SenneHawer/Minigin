#pragma once
#include "GameObject.h"

class FpsCounter final : public dae::GameObject
{
public:
	FpsCounter();
	~FpsCounter();

	virtual void Update(GameContext* gameContext) override;
private:

};

