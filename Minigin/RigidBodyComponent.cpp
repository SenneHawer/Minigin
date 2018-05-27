#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include <SDL.h>
#include "Renderer.h"
#include "TransformComponent.h"
#include "GameObject.h"


RigidBodyComponent::RigidBodyComponent(float width, float height, float rayDistance, sen::float2 posOffset)
	:m_Width(width)
	, m_Height(height)
	, m_RayDistance(rayDistance)
	, m_Offset(posOffset)
	, correction(5.0f)
{
}


RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Initialize()
{
}

void RigidBodyComponent::Update()
{
	//Center position


	m_Position = GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
	//m_Position.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + m_Width / 2;
	//m_Position.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + m_Height / 2;
	//m_Position.x = 300;
	//m_Position.y = 200;

	m_Position.x += m_Offset.x;
	m_Position.y += m_Offset.y;

	//RayPositions
	glm::vec3 centerPos = glm::vec3(m_Position.x + m_Width / 2, m_Position.y + m_Height / 2, 0.0f);
	m_UpPoint = m_DownPoint = m_LeftPoint = m_RightPoint = centerPos;

	m_UpPoint.y -= m_RayDistance;
	m_DownPoint.y += m_RayDistance;
	m_LeftPoint.x -= m_RayDistance;
	m_RightPoint.x += m_RayDistance;

}

bool RigidBodyComponent::IsOverlapping(glm::vec3 position, float width, float height)
{
	if (m_Position.x < position.x + width &&
		m_Position.x + m_Width > position.x &&
		m_Position.y < position.y + height &&
		m_Position.y + m_Height > position.y)
	{
		return true;
	}
	else
		return false;
}

bool RigidBodyComponent::IsOverlapping(RigidBodyComponent* rigidbody)
{
	auto position = rigidbody->GetPosition();
	auto width = rigidbody->GetWidth();
	auto height = rigidbody->GetHeight();

	if (m_Position.x < position.x + width &&
		m_Position.x + m_Width > position.x &&
		m_Position.y < position.y + height &&
		m_Position.y + m_Height > position.y)
	{
		return true;
	}
	else
		return false;
}

bool RigidBodyComponent::IsUpOverlapping(glm::vec3 position, float width, float height)
{
	//if (m_UpPoint.x > position.x && m_UpPoint.x < position.x + width &&
	//	m_UpPoint.y > position.y && m_UpPoint.y < position.y + height)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	glm::vec3 centerPos = glm::vec3(m_Position.x + m_Width / 2, m_Position.y + m_Height / 2, 0.0f);

	glm::vec3 pL;
	pL.x = centerPos.x - m_Width / 2.0f; 
	pL.y = centerPos.y - m_Height / 2.0f;
	//pL.x -= correction;
	pL.y -= correction;


	glm::vec3 pR;
	pR.x = centerPos.x + m_Width / 2.0f; 
	pR.y = centerPos.y - m_Height / 2.0f;
	//pR.x += correction;
	pR.y -= correction;

	if (pL.x > position.x && pL.x < position.x + width &&
		pL.y > position.y && pL.y < position.y + height ||
		pR.x > position.x && pR.x < position.x + width &&
		pR.y > position.y && pR.y < position.y + height)
	{
		return true;
	}
	else
		return false;
}
bool RigidBodyComponent::IsDownOverlapping(glm::vec3 position, float width, float height)
{
	//if (m_DownPoint.x > position.x && m_DownPoint.x < position.x + width &&
	//	m_DownPoint.y > position.y && m_DownPoint.y < position.y + height)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	glm::vec3 centerPos = glm::vec3(m_Position.x + m_Width / 2, m_Position.y + m_Height / 2, 0.0f);

	glm::vec3 pL;
	pL.x = centerPos.x - m_Width / 2.0f;
	pL.y = centerPos.y + m_Height / 2.0f;
	//pL.x -= correction;
	pL.y += correction;

	glm::vec3 pR;
	pR.x = centerPos.x + m_Width / 2.0f;
	pR.y = centerPos.y + m_Height / 2.0f;
	//pR.x += correction;
	pR.y += correction;

	if (pL.x > position.x && pL.x < position.x + width &&
		pL.y > position.y && pL.y < position.y + height ||
		pR.x > position.x && pR.x < position.x + width &&
		pR.y > position.y && pR.y < position.y + height)
	{
		return true;
	}
	else
		return false;
}
bool RigidBodyComponent::IsLeftOverlapping(glm::vec3 position, float width, float height)
{
	glm::vec3 centerPos = glm::vec3(m_Position.x + m_Width / 2, m_Position.y + m_Height / 2, 0.0f);

	glm::vec3 pU;
	pU.x = centerPos.x - m_Width / 2.0f;
	pU.y = centerPos.y - m_Height / 2.0f;
	pU.x -= correction;
	//pU.y -= correction;

	glm::vec3 pD;
	pD.x = centerPos.x - m_Width / 2.0f;
	pD.y = centerPos.y + m_Height / 2.0f;
	pD.x -= correction;
	//pD.y += correction;

	if ((pU.x > position.x && pU.x < position.x + width) && (pU.y > position.y && pU.y < position.y + height) ||
		(pD.x > position.x && pD.x < position.x + width) && (pD.y > position.y && pD.y < position.y + height))
	{
		return true;
	}
	else
	{
		return false;
	}

	//||
	//	pD.x > position.x && pD.x < position.x + width &&
	//	pD.y > position.y && pD.y < position.y + height



	//UNREFERENCED_PARAMETER(height);
	//if (pU.x > position.x && pU.x < position.x + width &&
	//	pU.y > position.y && pU.y < position.y + height)
	//{
	//	return true;
	//}
	//else
	//	return false;
}
bool RigidBodyComponent::IsRightOverlapping(glm::vec3 position, float width, float height)
{
	//if (m_RightPoint.x > position.x && m_RightPoint.x < position.x + width &&
	//	m_RightPoint.y > position.y && m_RightPoint.y < position.y + height)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}

	glm::vec3 centerPos = glm::vec3(m_Position.x + m_Width / 2, m_Position.y + m_Height / 2, 0.0f);

	glm::vec3 pU;
	pU.x = centerPos.x + m_Width / 2.0f;
	pU.y = centerPos.y - m_Height / 2.0f;
	pU.x += correction;
	//pU.y -= correction;

	glm::vec3 pD;
	pD.x = centerPos.x + m_Width / 2.0f;
	pD.y = centerPos.y + m_Height / 2.0f;
	pD.x += correction;
	//pD.y += correction;

	if ((pU.x > position.x && pU.x < position.x + width) && (pU.y > position.y && pU.y < position.y + height) ||
		(pD.x > position.x && pD.x < position.x + width) && (pD.y > position.y && pD.y < position.y + height))
	{
		return true;
	}
	else
	{
		return false;
	}
}


float RigidBodyComponent::GetHeight()
{
	return m_Height;
}

float RigidBodyComponent::GetWidth()
{
	return m_Width;
}

glm::vec3 RigidBodyComponent::GetPosition()
{
	return m_Position;
}
std::vector<glm::vec3> RigidBodyComponent::GetRayPoints()
{
	std::vector<glm::vec3> vector;
	vector.push_back(m_UpPoint);
	vector.push_back(m_DownPoint);
	vector.push_back(m_LeftPoint);
	vector.push_back(m_RightPoint);

	return vector;
}