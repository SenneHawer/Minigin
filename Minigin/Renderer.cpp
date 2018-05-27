#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include <algorithm>

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	SDL_GetWindowSize(window, &m_WindowWidth, &m_WindowHeight);
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	//SceneManager::GetInstance().Render();

	std::for_each(m_pRenderComponents.begin(), m_pRenderComponents.end(), [&](RenderComponent* comp)
	{
		comp->Render(mRenderer);
	});

	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

//RenderComponent& dae::Renderer::AddRenderComponent(const Texture2D& texture, const float xPos, const float yPos)
//{
//	RenderComponent* renderComp = new RenderComponent(texture.GetSDLTexture(), xPos, yPos);
//	m_pRenderComponents.push_back(renderComp);
//	//UNREFERENCED_PARAMETER(renderComp);
//
//	return *renderComp;
//}

void dae::Renderer::NotifyRender(RenderComponent* renderComp)
{
	//if (renderComp)
	m_pRenderComponents.push_back(renderComp);
}
void dae::Renderer::DeNotifyRenderer(RenderComponent* renderComp)
{
	auto it = std::find(m_pRenderComponents.begin(), m_pRenderComponents.end(), renderComp);

	m_pRenderComponents.erase(it);
}
void dae::Renderer::EmptyRenderer()
{
	auto size = m_pRenderComponents.size();
	for (unsigned int i{}; i < size; ++i)
	{
		m_pRenderComponents.erase(m_pRenderComponents.begin());
	}

}


int dae::Renderer::GetWindowWidth()
{
	return m_WindowWidth;
}

int dae::Renderer::GetWindowHeight()
{
	return m_WindowHeight;
}

