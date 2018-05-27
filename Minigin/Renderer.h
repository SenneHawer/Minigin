#pragma once
#include <vector>
#include "Singleton.h"
#include "RenderComponent.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		int GetWindowWidth();
		int GetWindowHeight();

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }

		void NotifyRender(RenderComponent* renderComp);
		void DeNotifyRenderer(RenderComponent* renderComp);
		void EmptyRenderer();

	//	RenderComponent& AddRenderComponent(const Texture2D& texture, const float xPos, const float yPos);

	private:
		int m_WindowWidth;
		int m_WindowHeight;

		std::vector<RenderComponent*> m_pRenderComponents;

	};
}

