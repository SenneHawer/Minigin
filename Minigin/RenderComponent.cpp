#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include <SDL.h>
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "TextComponent.h"

RenderComponent::RenderComponent(bool renderRigid, bool renderTexture, bool renderText)
	:m_RenderRigid(renderRigid)
	,m_RenderTexture(renderTexture)
	,m_RenderText(renderText)
	,m_DebugColor(255.0f, 255.0f, 255.0f)
{
}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::Initialize()
{
	//m_pTexture = GetGameObject()->GetComponent<TextureComponent>()->GetTexture();
}


void RenderComponent::Render(SDL_Renderer* sdl_renderer)
{
	UNREFERENCED_PARAMETER(sdl_renderer);
	//Get game obj
	auto obj = GetGameObject();

	//Get pos
	auto pos = obj->GetComponent<TransformComponent>()->GetPosition();

	if (m_RenderTexture)
	{
		auto texture = obj->GetComponent<TextureComponent>()->GetTexture();
		auto textureWidth = obj->GetComponent<TextureComponent>()->GetTextureWidth();
		auto textureHeight = obj->GetComponent<TextureComponent>()->GetTextureHeight();

		RenderTexture(sdl_renderer, *texture, pos.x, pos.y, float(textureWidth), float(textureHeight));
	}

	if (m_RenderText)
	{
		auto text = obj->GetComponent<TextComponent>()->GetTexture();
		auto textureWidth = obj->GetComponent<TextComponent>()->GetTextureWidth();
		auto textureHeight = obj->GetComponent<TextComponent>()->GetTextureHeight();

		RenderTexture(sdl_renderer, *text, pos.x, pos.y, float(textureWidth), float(textureHeight));
	}

	if (m_RenderRigid)
	{
		auto height = obj->GetComponent<RigidBodyComponent>()->GetHeight();
		auto width = obj->GetComponent<RigidBodyComponent>()->GetWidth();
		RenderDebugRect(sdl_renderer, pos.x, pos.y, width, height);

		auto points = obj->GetComponent<RigidBodyComponent>()->GetRayPoints();
		for (auto p : points)
		{
			SDL_RenderDrawLine(sdl_renderer, int(pos.x + width/2), int(pos.y + width/2), int(p.x), int(p.y));
		}
		
		//SDL_RenderDrawPoint(sdl_renderer, int(pos.x + width/2), int(pos.y + height/2));
	}
}


//PRIVATE
void RenderComponent::RenderTexture(SDL_Renderer* sdl_renderer, const dae::Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);

	if (width > 0 && height > 0)
	{
		dst.w = static_cast<int>(width);
		dst.h = static_cast<int>(height);
	}
	else
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	
	SDL_RenderCopy(sdl_renderer, texture.GetSDLTexture(), nullptr, &dst);
}

void RenderComponent::RenderDebugRect(SDL_Renderer* sdl_renderer, const float x, const float y, const float width, const float height) const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(x);
	rect.y = static_cast<int>(y);

	rect.w = static_cast<int>(width);
	rect.h = static_cast<int>(height);

	SDL_SetRenderDrawColor(sdl_renderer, Uint8(m_DebugColor.x), Uint8(m_DebugColor.y), Uint8(m_DebugColor.z), 255);
	SDL_RenderDrawRect(sdl_renderer, &rect);
}

void RenderComponent::SetDebugColor(glm::vec3 color)
{
	m_DebugColor = color;
}
