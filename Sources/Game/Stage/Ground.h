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


class Ground : public GameObject
{
public:
	Ground(DirectX::SimpleMath::Vector3& pos);
	~Ground();

public:
	void Update(const DX::StepTimer& timer) override;
	void Render(const DX::StepTimer& timer) override;
	
	//当たり判定
	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr)override;
	
private:
	//モデルデータ
	std::unique_ptr<DirectX::Model> m_model;
	//当たり判定
	std::unique_ptr<BoxCollider>  m_collider;
	//デバックボックス
	std::unique_ptr<DirectX::GeometricPrimitive> m_debugBox;
	DirectX::SimpleMath::Color                   m_color;
};

