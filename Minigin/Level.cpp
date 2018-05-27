#include "MiniginPCH.h"
#include "Level.h"
#include "RigidBodyComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include <fstream>
#include <algorithm>
#include "PointPickUp.h"
#include "LevelTile.h"
#include "Pacman.h"
#include "Crossing.h"
#include "PowerPickUp.h"
#include "Ghost.h"
#include "Ghostman.h"

Level::Level()
{
	m_pLevelTileHolder = new LevelTileHolder();
	AddChild(m_pLevelTileHolder);
	m_pPickUpHolder = new PickUpHolder();
	AddChild(m_pPickUpHolder);
	m_pCrossingHolder = new CrossingHolder();
	AddChild(m_pCrossingHolder);
}


Level::~Level()
{
}

void Level::CreateLevel(const std::string& assetFile, int tileAmountX, int tileAmountY)
{
	std::ifstream file{ assetFile };

	float tileWidth = float(dae::Renderer::GetInstance().GetWindowWidth()) / float(tileAmountX);
	float tileHeight = float(dae::Renderer::GetInstance().GetWindowHeight()) / float(tileAmountY);

	for (int row = 0; row < tileAmountY; ++row)
	{
		std::string line;
		std::getline(file, line);

		for (int col = 0; col < tileAmountX; ++col)
		{
			if (line.at(col) == '-')
			{
				auto levelTile = new LevelTile(tileWidth + 1, tileHeight + 1, "Wall_Hor.png");

				levelTile->GetTransform()->SetPosition(col * tileWidth, row * tileHeight);
				m_pLevelTileHolder->AddChild(levelTile);
			}
			else if (line.at(col) == '!')
			{
				auto levelTile = new LevelTile(tileWidth + 1, tileHeight + 1, "Wall_Ver.png");

				levelTile->GetTransform()->SetPosition(col * tileWidth, row * tileHeight);
				m_pLevelTileHolder->AddChild(levelTile);
			}
			else if (line.at(col) == '*')
			{
				auto pickUp = new PointPickUp();
				pickUp->GetTransform()->SetPosition(col * tileWidth + 5, row * tileHeight + 5);
				m_pPickUpHolder->AddChild(pickUp);
			}
			else if (line.at(col) == '+')
			{
				//Crossing
				auto crossing = new Crossing();
				crossing->GetTransform()->SetPosition(col * tileWidth + 5, row * tileHeight + 5);
				m_pCrossingHolder->AddChild(crossing);

				//PickUp
				auto pickUp = new PointPickUp();
				pickUp->GetTransform()->SetPosition(col * tileWidth + 5, row * tileHeight + 5);
				m_pPickUpHolder->AddChild(pickUp);
			}
			else if (line.at(col) == 'O')
			{
				auto pickUp = new PowerPickUp();
				pickUp->GetTransform()->SetPosition(col * tileWidth + 5, row * tileHeight + 5);
				m_pPickUpHolder->AddChild(pickUp);
			}
			else if (line.at(col) == '1')
			{
				auto levelTile = new LevelTile(tileWidth + 1, tileHeight + 1, "Wall_Cor_LD.png");

				levelTile->GetTransform()->SetPosition(col * tileWidth, row * tileHeight);
				m_pLevelTileHolder->AddChild(levelTile);
			}
			else if (line.at(col) == '2')
			{
				auto levelTile = new LevelTile(tileWidth + 1, tileHeight + 1, "Wall_Cor_LU.png");

				levelTile->GetTransform()->SetPosition(col * tileWidth, row * tileHeight);
				m_pLevelTileHolder->AddChild(levelTile);
			}
			else if (line.at(col) == '3')
			{
				auto levelTile = new LevelTile(tileWidth + 1, tileHeight + 1, "Wall_Cor_RD.png");

				levelTile->GetTransform()->SetPosition(col * tileWidth, row * tileHeight);
				m_pLevelTileHolder->AddChild(levelTile);
			}
			else if (line.at(col) == '4')
			{
				auto levelTile = new LevelTile(tileWidth + 1, tileHeight + 1, "Wall_Cor_RU.png");

				levelTile->GetTransform()->SetPosition(col * tileWidth, row * tileHeight);
				m_pLevelTileHolder->AddChild(levelTile);
			}
			else if (line.at(col) == '7')
			{
				auto levelTile = new LevelTile(tileWidth + 1, tileHeight + 1, "Wall_TCor_VL.png");

				levelTile->GetTransform()->SetPosition(col * tileWidth, row * tileHeight);
				m_pLevelTileHolder->AddChild(levelTile);
			}
			else if (line.at(col) == '8')
			{
				auto levelTile = new LevelTile(tileWidth + 1, tileHeight + 1, "Wall_TCor_VR.png");

				levelTile->GetTransform()->SetPosition(col * tileWidth, row * tileHeight);
				m_pLevelTileHolder->AddChild(levelTile);
			}
		}
	}
}

void Level::UpdateCollision(dae::GameObject* otherObj, sen::Vector2f& velocity)
{
	UNREFERENCED_PARAMETER(otherObj);
	UNREFERENCED_PARAMETER(velocity);
	//auto otherComp = otherObj->GetComponent<RigidBodyComponent>();

	m_pLevelTileHolder->UpdateCollision(otherObj, velocity);

	auto ghost = dynamic_cast<Ghostman*>(otherObj);
	if (ghost == NULL)
	{
		auto other = dynamic_cast<Pacman*>(otherObj);
		if (other != NULL) //if NULL -> cast failed
		{
			m_pPickUpHolder->UpdateCollisions(otherObj);
		}
	}

	if (dynamic_cast<Ghost*>(otherObj))
		m_pCrossingHolder->UpdateCollision(otherObj, velocity);
}

int Level::GetScore()
{
	return m_pPickUpHolder->GetScore();
}


