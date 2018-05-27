#include "MiniginPCH.h"
#include "CrossingHolder.h"
#include <algorithm>
#include "Vector2f.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Crossing.h"


CrossingHolder::CrossingHolder()
{
}


CrossingHolder::~CrossingHolder()
{
}

void CrossingHolder::UpdateCollision(dae::GameObject* otherObj, sen::Vector2f& velocity)
{
	UNREFERENCED_PARAMETER(otherObj);
	UNREFERENCED_PARAMETER(velocity);
	std::for_each(m_pChildObjects.begin(), m_pChildObjects.end(), [&](dae::GameObject* obj)
	{
		auto crossing = static_cast<Crossing*>(obj);

		auto rigid = crossing->GetComponent<RigidBodyComponent>();

		auto otherObjCenterPos = otherObj->GetTransform()->GetPosition();
		otherObjCenterPos.x += otherObj->GetComponent<RigidBodyComponent>()->GetWidth() / 2;
		otherObjCenterPos.y += otherObj->GetComponent<RigidBodyComponent>()->GetHeight() / 2;

		if (rigid->IsOverlapping(otherObjCenterPos, 1, 1))
		{
			if (!crossing->IsUsed())
			{
				auto pos = crossing->GetTransform()->GetPosition();
				otherObj->GetTransform()->SetPosition(pos.x, pos.y);
				velocity.x = 0;
				velocity.y = 0;
				crossing->SetIsUsed(true);
				std::cout << "used" << std::endl;
			}
		}

		//if (!rigid->IsOverlapping(otherObj->GetComponent<RigidBodyComponent>()))
		//{
		//	crossing->SetIsUsed(false);
		//}
	});
}
