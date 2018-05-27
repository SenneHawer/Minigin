#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include <SDL.h>

TextureComponent::TextureComponent()
	:BaseComponent()
{
}

TextureComponent::~TextureComponent()
{
}

void TextureComponent::Update()
{
	m_Position = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
}

void TextureComponent::LoadTexture(const std::string& filename)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}

std::shared_ptr<dae::Texture2D> TextureComponent::GetTexture() const
{
	return m_pTexture;
}
void TextureComponent::SetDimensions(float width, float height)
{
	m_TextureWidth = int(width);
	m_TextureHeight = int(height);
}

void TextureComponent::Scale(float x, float y)
{
	if (!m_pTexture) std::cout << "m_pTexture = nullptr!" << std::endl;

	if (m_TextureHeight == -1 || m_TextureWidth == -1)
	{
		SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);

		m_TextureWidth = int(float(m_TextureWidth) * x);
		m_TextureHeight = int(float(m_TextureHeight) * y);
	}
}

int TextureComponent::GetTextureWidth()
{
	return m_TextureWidth;
}
int TextureComponent::GetTextureHeight()
{
	return m_TextureHeight;
}

