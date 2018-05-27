#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "Vector2f.h"


TransformComponent::TransformComponent()
	:BaseComponent()
{
}


TransformComponent::~TransformComponent()
{
}

const glm::vec3& TransformComponent::GetPosition() const
{
	return m_Position;
}

void TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
void TransformComponent::SetPosition(glm::vec3 position)
{
	m_Position = position;
}
void TransformComponent::Translate(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
}


void TransformComponent::Update()
{
}

void TransformComponent::Move(sen::Vector2f velocity, float elapsedSec)
{
	sen::Vector2f tempPos;
	tempPos.x = float(m_Position.x);
	tempPos.y = float(m_Position.y);

	tempPos += velocity * elapsedSec;

	m_Position.x = tempPos.x;
	m_Position.y = tempPos.y;
}
