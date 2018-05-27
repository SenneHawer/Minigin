#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

#include "BaseComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "TestScene.h"
#include "CollisionTestScene.h"
#include "LevelTestScene.h"
#include "PacmanScene.h"
#include "TextScene.h"
#include "MenuScene.h"
#include "GameOverScene.h"
#include "MultiplayerScene.h"
#include "MultiplayerGhostScene.h"
#include "WinningScene.h"

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		640,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//SceneManager::GetInstance().ActivateScene(std::make_shared<TestScene>());
	//SceneManager::GetInstance().ActivateScene(std::make_shared<CollisionTestScene>());
	//SceneManager::GetInstance().ActivateScene(std::make_shared<LevelTestScene>());
	//SceneManager::GetInstance().ActivateScene(std::make_shared<PacmanScene>());
	//SceneManager::GetInstance().ActivateScene(std::make_shared<TextScene>());

	SceneManager::GetInstance().AddScene(std::make_shared<MenuScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<PacmanScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<MultiplayerScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<MultiplayerGhostScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<GameOverScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<WinningScene>());
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		float lag = 0.0f;

		while (doContinue)
		{
			//Handle Time
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float, std::milli>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			
			//Check Continue
			doContinue = input.ProcessInput();
			input.Update();

			while (lag >= msPerFrame)
			{
				sceneManager.Update(deltaTime);
				lag -= msPerFrame;
			}
			UNREFERENCED_PARAMETER(renderer);
			renderer.Render();
		}
	}

	Cleanup();
}
