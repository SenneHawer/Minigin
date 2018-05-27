#pragma once
#include "TextureComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Font;
}

class TextComponent final : public TextureComponent
{
public:
	TextComponent();
	~TextComponent();

	void Initialize() override {}
	void Update() override;

	void LoadFont(const std::string& filename, unsigned int size);

	void SetPositionOffset(glm::vec3 offset);
	void SetText(const std::string& text);

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	glm::vec3 m_PositionOffset;
	std::shared_ptr<dae::Font> m_pFont;
};

