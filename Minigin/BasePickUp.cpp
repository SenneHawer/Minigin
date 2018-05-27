#include "MiniginPCH.h"
#include "BasePickUp.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"


BasePickUp::BasePickUp(const std::string& assetFile)
{
	auto textureComp = new TextureComponent();
	textureComp->LoadTexture(assetFile);
	textureComp->SetDimensions(10, 10);
	this->AddComponent(textureComp);

	auto rigidbody = new RigidBodyComponent(10, 10, 0);
	this->AddComponent(rigidbody);

	auto renderComp = new RenderComponent(false, true);
	this->AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
}


BasePickUp::~BasePickUp()
{
}

void BasePickUp::Update(GameContext* gameContext)
{
	UNREFERENCED_PARAMETER(gameContext);
	GameObject::Update(gameContext);

}

bool BasePickUp::IsOverlapping(GameObject* player)
{
	auto rigid = this->GetComponent<RigidBodyComponent>();
	auto otherRigid = player->GetComponent<RigidBodyComponent>();

	if (rigid->IsOverlapping(otherRigid->GetPosition(), otherRigid->GetWidth(), otherRigid->GetHeight()))
	{
		return true;
	}
	else
		return false;
}

