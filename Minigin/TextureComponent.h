#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <memory>
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)


class TextureComponent : public BaseComponent
{
public:
	TextureComponent();
	virtual ~TextureComponent();

	void Initialize() override {}
	void Update() override;

	void LoadTexture(const std::string& fileName);
	void Scale(float x, float y);
	void SetDimensions(float width, float height);

	std::shared_ptr<dae::Texture2D> GetTexture() const;
	int GetTextureWidth();
	int GetTextureHeight();

	


protected:
	std::shared_ptr<dae::Texture2D> m_pTexture;
	glm::vec3 m_Position;

	int m_TextureWidth = -1;
	int m_TextureHeight = -1;
};

