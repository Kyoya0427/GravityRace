//======================================================
// File Name	: Collider.cpp
// Summary	: コライダーインターフェイス
// Author		: Kyoya Sakamoto
//======================================================
//#include <pch.h>

#include "Collider.h"

#include <Game\Object\GameObject.h>

/// <summary>
/// コンストラク
/// </summary>
/// <param name="owner"></param>
Collider::Collider(GameObject* owner)
	: m_owner(owner)
	, m_offset(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f))
{
}


bool Collider::IsCollided(const MoveBoxCollider * collider, RaycastHit* raycastHit) const
{
	collider;
	raycastHit;
	assert(false && "This collision detection is not implemented.");

	return false;
}

bool Collider::IsCollided(const BoxCollider* collider, RaycastHit* raycastHit) const
{
	collider;
	raycastHit;
	assert(false && "This collision detection is not implemented.");

	return false;
}




void Collider::HitContact(const Collider* object, RaycastHit* raycastHit) const
{
	m_owner->HitContact(object->m_owner,raycastHit);
}



const DirectX::SimpleMath::Vector3 Collider::GetPosition() const
{
	return m_owner->GetPosition() + m_offset;
}

const DirectX::SimpleMath::Vector3 Collider::GetOffset() const
{
	return m_offset;
}


void Collider::SetOffset(const DirectX::SimpleMath::Vector3 & offset)
{
	m_offset = offset;
}
