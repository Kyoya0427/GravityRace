//======================================================
// File Name	: Collider.h
// Summary	: コライダーインターフェイス
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SimpleMath.h>
#include "RaycastHit.h"

class GameObject;
class BoxCollider;
class MoveBoxCollider;

class Collider
{
protected:
	GameObject*                  m_owner;
	DirectX::SimpleMath::Vector3 m_offset;

public:
	Collider(GameObject* owner);

public:
	virtual ~Collider() = default;


public:
	virtual bool IsCollided(const Collider*       collider, RaycastHit* raycastHit = nullptr) const = 0;
	virtual bool IsCollided(const MoveBoxCollider* collider, RaycastHit* raycastHit = nullptr) const;
	virtual bool IsCollided(const BoxCollider*    collider, RaycastHit* raycastHit = nullptr) const;


public:
	void HitContact   (const Collider* object, RaycastHit* raycastHit = nullptr) const;

	const DirectX::SimpleMath::Vector3 GetPosition() const;
	const DirectX::SimpleMath::Vector3 GetOffset() const;
	void  SetOffset(const DirectX::SimpleMath::Vector3& offset);

};
