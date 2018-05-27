#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <SDL.h>
#include <glm/detail/type_vec3.hpp>

class RenderComponent final : public BaseComponent
{
public:
	RenderComponent(bool renderRigid = false, bool renderTexture = false, bool renderText = false);
	~RenderComponent();

	void Initialize() override;
	void Update() override {};

	void Render(SDL_Renderer* sdl_renderer);
	void RenderTexture(SDL_Renderer* sdl_renderer, const dae::Texture2D& texture, float x, float y, const float width = -1.0f, const float height = -1.0f) const;
	void RenderDebugRect(SDL_Renderer* sdl_renderer, float x, float y, const float width, const float height) const;
	void RenderDebugLine(SDL_Renderer* sdl_renderer, glm::vec3 begin, glm::vec3 end);

	void SetDebugColor(glm::vec3 color);
	//void SetTexture

private:
	std::shared_ptr<dae::Texture2D> m_pTexture;
	bool m_RenderRigid;
	bool m_RenderTexture;
	bool m_RenderText;
	glm::vec3 m_DebugColor;

	//float m_TextureWidth = -1;
	//float m_TextureHeight = -1;
};

