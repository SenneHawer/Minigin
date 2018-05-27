#include "MiniginPCH.h"
#include "LevelTile.h"
#include "RigidBodyComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "TextureComponent.h"


LevelTile::LevelTile(float tileWidth, float tileHeight, std::string assetFile)
{
	//RigidBody Component
	auto textureComp = new TextureComponent();
	textureComp->LoadTexture(assetFile);
	AddComponent(textureComp);

	auto rigidbody = new RigidBodyComponent(tileWidth, tileHeight, 0);
	AddComponent(rigidbody);

	auto renderComp = new RenderComponent(false, true, false);
	AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
}


LevelTile::~LevelTile()
{
}
