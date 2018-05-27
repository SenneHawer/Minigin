#pragma once
#include "GameObject.h"

namespace sen {
	class Vector2f;
}

class CrossingHolder final : public dae::GameObject
{
public:
	CrossingHolder();
	virtual ~CrossingHolder();

	void UpdateCollision(dae::GameObject* otherObj, sen::Vector2f& velocity);

};

