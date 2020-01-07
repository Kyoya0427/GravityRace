//======================================================
// File Name	: MoveBoxCollider.cpp
// Summary	: “®‚­” 
// Author		: Kyoya Sakamoto
//======================================================

#include "MoveBoxCollider.h"
#include "CollisionManager.h"

#include <Object\GameObject.h>

MoveBoxCollider::MoveBoxCollider(GameObject * owner, const DirectX::SimpleMath::Vector3 & size)
	:Collider(owner)
	,m_size(size)
{
}

bool MoveBoxCollider::IsCollided(const Collider * collider, RaycastHit* raycastHit) const
{
	return collider->IsCollided(this,raycastHit);
}

bool MoveBoxCollider::IsCollided(const MoveBoxCollider * collider, RaycastHit* raycastHit) const
{
	raycastHit;
	return CollisionManager::IsCollided(this, collider);
}

bool MoveBoxCollider::IsCollided(const BoxCollider * collider, RaycastHit* raycastHit) const
{
	return CollisionManager::IsCollided(this, collider,raycastHit);
}
