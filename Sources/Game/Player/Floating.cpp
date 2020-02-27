//======================================================
// File Name	: Floating.cpp
// Summary	: ƒWƒƒƒ“ƒvˆ—
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "Floating.h"


Floating::Floating()
{
}

void Floating::Initialize(Player * player)
{
	m_player = player;
	m_count = 0;
	m_speed = 0.0f;
}

void Floating::Update(const DX::StepTimer& timer)
{
	timer;
	
	m_player->SetVelY(m_speed);
	if (m_count == 0)
	{
		m_player->SetVelocity(DirectX::SimpleMath::Vector3::Zero);
	}
	
	if (m_count < 10)
	{
		m_speed += 0.1f;
	}
	if (m_count > 10)
	{
		m_speed -= 0.1f;
	}
	if (m_count >= 20)
	{
		m_player->ChaneAgravityState();
		m_speed = 0.0f;
		m_count = 0;
	}
	m_count++;
}

void Floating::Render(const DX::StepTimer& timer)
{
	timer;
}
