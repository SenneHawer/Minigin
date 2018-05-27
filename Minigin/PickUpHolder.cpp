#include "MiniginPCH.h"
#include "PickUpHolder.h"
#include <algorithm>
#include "BasePickUp.h"
#include "PointPickUp.h"
#include "RenderComponent.h"
#include "PowerPickUp.h"
#include "Pacman.h"


PickUpHolder::PickUpHolder()
	:m_Score(0)
{
}


PickUpHolder::~PickUpHolder()
{
}

void PickUpHolder::UpdateCollisions(dae::GameObject* player)
{
	UNREFERENCED_PARAMETER(player);
	for (unsigned int i = 0; i < m_pChildObjects.size(); ++i)
	{
		auto pickUp = dynamic_cast<PointPickUp*>(m_pChildObjects.at(i));
		if (pickUp)
		{
			if (pickUp->IsOverlapping(player))
			{
				++m_Score;

				RemoveChild(m_pChildObjects.at(i));
				continue;
			}
			else
			{
				m_pChildObjects.at(i)->GetComponent<RenderComponent>()->SetDebugColor(glm::vec3(255, 255, 255));
				continue;
			}
		}

		auto power = dynamic_cast<PowerPickUp*>(m_pChildObjects.at(i));
		if (power)
		{
			if (power->IsOverlapping(player))
			{
				static_cast<Pacman*>(player)->MakeAngry();
				RemoveChild(m_pChildObjects.at(i));
				continue;
			}
		}

	}
}

int PickUpHolder::GetScore()
{
	return m_Score;
}
