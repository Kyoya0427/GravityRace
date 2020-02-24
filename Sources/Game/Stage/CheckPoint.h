#pragma once
//======================================================
// File Name	: Ground.h
// Summary	: 地面
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Model.h>
#include <GeometricPrimitive.h>

#include <Game\Object\GameObject.h>
#include <Game\Collider\BoxCollider.h>


class CheckPoint : public GameObject
{
public:
	CheckPoint(DirectX::SimpleMath::Vector3& pos);
	~CheckPoint();

public:
	void Update(float elapsedTime) override;
	void Render() override;

	//当たり判定
	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr)override;

private:
	//当たり判定
	std::unique_ptr<BoxCollider>  m_collider;
	//デバックボックス
	std::unique_ptr<DirectX::GeometricPrimitive> m_model;
	DirectX::SimpleMath::Color                   m_color;
};