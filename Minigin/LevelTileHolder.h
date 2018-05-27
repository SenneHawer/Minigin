#pragma once
#include "GameObject.h"

namespace sen {
	class Vector2f;
}

class LevelTileHolder final : public dae::GameObject
{
public:
	LevelTileHolder();
	~LevelTileHolder();

	void UpdateCollision(dae::GameObject* otherObj, sen::Vector2f& velocity);

};

