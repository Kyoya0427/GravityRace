//======================================================
// File Name	: MoveBoxCollider.h
// Summary	: 動く箱
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "Collider.h"

class MoveBoxCollider : public Collider
{
private:
	DirectX::SimpleMath::Vector3 m_size;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_velocity;

public:
	MoveBoxCollider(GameObject* owner, const DirectX::SimpleMath::Vector3& size);

public:
	~MoveBoxCollider() = default;

public:
	bool IsCollided(const Collider*        collider, RaycastHit* raycastHit = nullptr) const override;
	bool IsCollided(const MoveBoxCollider* collider, RaycastHit* raycastHit = nullptr) const override;
	bool IsCollided(const BoxCollider*     collider, RaycastHit* raycastHit = nullptr) const override;

public:
	const DirectX::SimpleMath::Vector3& GetSize() const;
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	const DirectX::SimpleMath::Vector3& Getvelocity() const;

public:
	void SetSize(const DirectX::SimpleMath::Vector3& size);
	void SetPosition(const DirectX::SimpleMath::Vector3& pos);
	void SetVelocity(const DirectX::SimpleMath::Vector3& vel);
};

/// <summary>
/// サイズ取得
/// </summary>
/// <returns></returns>
const inline DirectX::SimpleMath::Vector3& MoveBoxCollider::GetSize() const
{
	return m_size;
}

/// <summary>
/// 座標取得
/// </summary>
/// <returns></returns>
const inline DirectX::SimpleMath::Vector3& MoveBoxCollider::GetPosition() const
{
	return m_position;
}

/// <summary>
/// 速度を取得
/// </summary>
/// <returns></returns>
const inline DirectX::SimpleMath::Vector3& MoveBoxCollider::Getvelocity() const
{
	return m_velocity;
}

/// <summary>
/// サイズを設定
/// </summary>
/// <param name="size"></param>
inline void MoveBoxCollider::SetSize(const DirectX::SimpleMath::Vector3& size)
{
	m_size = size;
}

/// <summary>
/// 座標を設定
/// </summary>
/// <param name="pos"></param>
inline void MoveBoxCollider::SetPosition(const DirectX::SimpleMath::Vector3& pos)
{
	m_position = pos;
}

/// <summary>
/// 速度を設定
/// </summary>
/// <param name="vel"></param>
inline void MoveBoxCollider::SetVelocity(const DirectX::SimpleMath::Vector3& vel)
{
	m_velocity = vel;
}

















