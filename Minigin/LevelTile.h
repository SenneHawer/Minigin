#pragma once
#include "GameObject.h"

class LevelTile final : public dae::GameObject
{
public:
	LevelTile(float tileWidth, float tileHeight, std::string assetFile);
	~LevelTile();

	//void Update(GameContext* gameContext) override;

private:

};

