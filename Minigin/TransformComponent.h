#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include "Vector2f.h"
#pragma warning(pop)

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent();
	~TransformComponent();

	void Initialize() override {}
	void Update() override;
	void Move(sen::Vector2f velocity, float elapsedSec);

	const glm::vec3& GetPosition() const;

	void SetPosition(float x, float y, float z = 0.0f);
	void SetPosition(glm::vec3 position);
	void Translate(float x, float y);

private:
	glm::vec3 m_Position;

};

