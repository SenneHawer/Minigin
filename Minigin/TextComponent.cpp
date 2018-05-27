#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "ResourceManager.h"

TextComponent::TextComponent()
	:TextureComponent()
	,m_Text ("NOT READY")
	,m_pFont (nullptr)
	,m_NeedsUpdate(true)
	,m_PositionOffset(0.0f, 0.0f, 0.0f)
{

}


TextComponent::~TextComponent()
{
}



void TextComponent::Update()
{
	TextureComponent::Update();

	if (m_NeedsUpdate && m_pFont != nullptr)
	{
		const SDL_Color color = { 255, 255, 255 };
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<dae::Texture2D>(texture);

		//put update off again
		//m_NeedsUpdate = false;
	}
}

void TextComponent::LoadFont(const std::string& filename, unsigned int size)
{
	m_pFont = dae::ResourceManager::GetInstance().LoadFont(filename, size);

	const SDL_Color color = { 255, 255, 255 };
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_pTexture = std::make_shared<dae::Texture2D>(texture);
}

void TextComponent::SetPositionOffset(glm::vec3 offset)
{
	m_PositionOffset = offset;
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}