#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include <glm/detail/type_vec3.hpp>
#include "Vector2f.h"

class RigidBodyComponent final : public BaseComponent
{
public:
	RigidBodyComponent(float width, float height, float rayDistance, sen::float2 posOffset = sen::float2(0.0f, 0.0f));
	~RigidBodyComponent();

	virtual void Initialize() override;
	virtual void Update() override;

	//Info
	float GetWidth();
	float GetHeight();
	glm::vec3 GetPosition();

	std::vector<glm::vec3> GetRayPoints();

	//Collision info
	bool IsOverlapping(glm::vec3 position, float width, float height);
	bool IsOverlapping(RigidBodyComponent* rigidbody);

	bool IsUpOverlapping(glm::vec3 position, float width, float height);
	bool IsDownOverlapping(glm::vec3 position, float width, float height);
	bool IsLeftOverlapping(glm::vec3 position, float width, float height);
	bool IsRightOverlapping(glm::vec3 position, float width, float height);

private:
	//AABB
	glm::vec3 m_Position;
	sen::float2 m_Offset;
	float m_Width;
	float m_Height;

	float correction;

	//Direction Lines
	glm::vec3 m_UpPoint;
	glm::vec3 m_DownPoint;
	glm::vec3 m_RightPoint;
	glm::vec3 m_LeftPoint;

	float m_RayDistance;

	//Debug
	bool m_IsDebugRendering;
	SDL_Rect m_DebugRect;
};

