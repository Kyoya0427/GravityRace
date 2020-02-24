//======================================================
// File Name	: BoxCollider.cpp
// Summary	: 箱
// Author		: Kyoya Sakamoto
//======================================================

#include "BoxCollider.h"
#include "CollisionManager.h"

#include <Game\Object\GameObject.h>

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner"></param>
/// <param name="size"></param>
BoxCollider::BoxCollider(GameObject* owner, const DirectX::SimpleMath::Vector3& size)
	: Collider(owner)
	, m_size(size)
{
}


bool BoxCollider::IsCollided(const Collider* collider, RaycastHit* raycastHit) const
{
	return collider->IsCollided(this,raycastHit);
}

bool BoxCollider::IsCollided(const MoveBoxCollider * collider, RaycastHit* raycastHit) const
{
	return CollisionManager::IsCollided(this,collider,raycastHit);
}

bool BoxCollider::IsCollided(const BoxCollider* collider, RaycastHit* raycastHit) const
{
	raycastHit;
	return CollisionManager::IsCollided(this, collider);
}


void BoxCollider::SetSize(const DirectX::SimpleMath::Vector3& size)
{
	m_size = size;
}


const DirectX::SimpleMath::Vector3& BoxCollider::GetSize() const
{
	return m_size;
}

void BoxCollider::SetCollisionCenter(const DirectX::SimpleMath::Vector3 & collisionPos)
{
	m_collisionPos = collisionPos;
}

const DirectX::SimpleMath::Vector3 & BoxCollider::GetCollisionCenter() const
{
	return m_collisionPos;
}

float BoxCollider::GetTopBoxPos() const
{
	return m_collisionPos.y + m_size.y / 2;
}

float BoxCollider::GetBotBoxPos() const
{
	return m_collisionPos.y - m_size.y / 2;
}

float BoxCollider::GetLeftBoxPos() const
{
	return m_collisionPos.x - m_size.x / 2;
}

float BoxCollider::GetRightBoxPos() const
{
	return m_collisionPos.x + m_size.x / 2;
}

float BoxCollider::GetFrontBoxPos() const
{
	return m_collisionPos.z + m_size.z / 2;
}

float BoxCollider::GetBackBoxPos() const
{
	return m_collisionPos.z - m_size.z / 2;
}


