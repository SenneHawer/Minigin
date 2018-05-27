#include "MiniginPCH.h"
#include "LevelTileHolder.h"
#include <algorithm>
#include "Vector2f.h"
#include "RigidBodyComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"


LevelTileHolder::LevelTileHolder()
{
}


LevelTileHolder::~LevelTileHolder()
{
}

void LevelTileHolder::UpdateCollision(dae::GameObject* otherObj, sen::Vector2f& velocity)
{
	std::for_each(m_pChildObjects.begin(), m_pChildObjects.end(), [&](dae::GameObject* levelTile)
	{
		auto levelTileRigid = levelTile->GetComponent<RigidBodyComponent>();

		if (otherObj->GetComponent<RigidBodyComponent>()->IsOverlapping(levelTileRigid->GetPosition(), levelTileRigid->GetWidth(), levelTileRigid->GetHeight()))
		{
			levelTile->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(255, 0, 0));

			//m_Velocity = {0,0};
			//if (!wasInside)
			//{
			//	m_Velocity = -m_Velocity*2;
			//	wasInside = true;
			//}

			if (velocity.x > 0) velocity.x = -1;
			else if (velocity.x < 0) velocity.x = 1;

			if (velocity.y > 0) velocity.y = -1;
			else if (velocity.y < 0) velocity.y = 1;
		}

		if (otherObj->GetComponent<RigidBodyComponent>()->IsUpOverlapping(levelTileRigid->GetPosition(), levelTileRigid->GetWidth(), levelTileRigid->GetHeight()))
		{
			levelTile->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
			if (velocity.y < 0) velocity.y = 0;
		}
		else if (otherObj->GetComponent<RigidBodyComponent>()->IsDownOverlapping(levelTileRigid->GetPosition(), levelTileRigid->GetWidth(), levelTileRigid->GetHeight()))
		{
			levelTile->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
			if (velocity.y > 0) velocity.y = 0;
		}
		else if (otherObj->GetComponent<RigidBodyComponent>()->IsLeftOverlapping(levelTileRigid->GetPosition(), levelTileRigid->GetWidth(), levelTileRigid->GetHeight()))
		{
			levelTile->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
			if (velocity.x < 0) velocity.x = 0;
		}
		else if (otherObj->GetComponent<RigidBodyComponent>()->IsRightOverlapping(levelTileRigid->GetPosition(), levelTileRigid->GetWidth(), levelTileRigid->GetHeight()))
		{
			levelTile->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(0, 255, 0));
			if (velocity.x > 0) velocity.x = 0;
		}
		else
		{
			levelTile->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(255, 255, 255));
		}
	});
}
