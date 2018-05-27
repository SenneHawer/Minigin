#pragma once
#include "GameObject.h"

class Crossing final : public dae::GameObject
{
public:
	Crossing();
	virtual ~Crossing();

	virtual void Update(GameContext* gameContext) override;

	void SetIsUsed(bool used);
	bool IsUsed();

private:
	bool m_IsUsed;
	float m_CoolDown;

};

