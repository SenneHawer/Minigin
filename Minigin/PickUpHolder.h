#pragma once
#include "GameObject.h"

class PickUpHolder final : public dae::GameObject
{
public:
	PickUpHolder();
	~PickUpHolder();

	void UpdateCollisions(dae::GameObject* player);
	int GetScore();

private:
	int m_Score;
};

