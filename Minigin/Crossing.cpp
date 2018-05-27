#include "MiniginPCH.h"
#include "Crossing.h"
#include "Renderer.h"
#include "TextureComponent.h"
#include "RigidBodyComponent.h"


Crossing::Crossing()
	:m_IsUsed(false)
{
	//RigidBody Component
	auto rigidbody = new RigidBodyComponent(10, 10, 0);
	AddComponent(rigidbody);

	auto renderComp = new RenderComponent(false, false, false);
	AddComponent(renderComp);
	dae::Renderer::GetInstance().NotifyRender(renderComp);
}


Crossing::~Crossing()
{
}

void Crossing::Update(GameContext* gameContext)
{
	dae::GameObject::Update(gameContext);

	float elapsedSec = gameContext->GetGameTime()->GetElapsedSec();

	if (m_IsUsed)
	{
		m_CoolDown += elapsedSec;

		if (m_CoolDown >= 3.0f)
		{
			m_IsUsed = false;
			m_CoolDown = 0.0f;
		}
	}

}


void Crossing::SetIsUsed(bool used)
{
	m_IsUsed = used;
}

bool Crossing::IsUsed()
{
	return m_IsUsed;
}
