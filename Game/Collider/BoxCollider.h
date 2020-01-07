//======================================================
// File Name	: BoxCollider.h
// Summary	: ” 
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
private:
	DirectX::SimpleMath::Vector3 m_size;
	DirectX::SimpleMath::Vector3 m_collisionPos;


public:
	BoxCollider(GameObject* owner, const DirectX::SimpleMath::Vector3& size);

public:
	~BoxCollider() = default;


public:
	bool IsCollided(const Collider*       collider,RaycastHit* raycastHit = nullptr) const override;
	bool IsCollided(const MoveBoxCollider*      collider, RaycastHit* raycastHit = nullptr) const override;
	bool IsCollided(const BoxCollider*    collider, RaycastHit* raycastHit = nullptr) const override;


public:
	void  SetSize(const DirectX::SimpleMath::Vector3& size);
	const DirectX::SimpleMath::Vector3& GetSize() const;

	void SetCollisionCenter(const DirectX::SimpleMath::Vector3& collisionPos);
	const DirectX::SimpleMath::Vector3& GetCollisionCenter() const;

	float GetTopBoxPos() const;
	float GetBotBoxPos() const;
	float GetLeftBoxPos() const;
	float GetRightBoxPos() const;
	float GetFrontBoxPos() const;
	float GetBackBoxPos() const;
};

