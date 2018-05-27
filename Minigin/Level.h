#pragma once
#include "GameObject.h"
#include "PickUpHolder.h"
#include "LevelTileHolder.h"
#include "CrossingHolder.h"

namespace sen {
	class Vector2f;
}

class Level : public dae::GameObject
{
public:
	Level();
	virtual ~Level();

	void UpdateCollision(dae::GameObject* otherObj, sen::Vector2f& velocity);
	void CreateLevel(const std::string& assetFile, int tileAmountX = 28, int tileAmountY = 30);

	int GetScore();

private:
	PickUpHolder* m_pPickUpHolder = nullptr;
	LevelTileHolder* m_pLevelTileHolder = nullptr;
	CrossingHolder* m_pCrossingHolder = nullptr;

};

