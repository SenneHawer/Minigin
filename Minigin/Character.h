#pragma once
#include <glm/detail/type_vec3.hpp>

class Character
{
public:
	Character();
	~Character();

	void Update();

	void SetPosition();
	glm::vec3 GetPosition();

private:

};

