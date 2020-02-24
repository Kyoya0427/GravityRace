//======================================================
// File Name	: Building.h
// Summary	: 地面
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Model.h>
#include <GeometricPrimitive.h>

#include <Game\Object\GameObject.h>
#include <Game\Collider\BoxCollider.h>


class Building : public GameObject
{
public:
	Building(DirectX::SimpleMath::Vector3& pos, DirectX::SimpleMath::Vector3& size);
	~Building();

public:
	void Update(float elapsedTime) override;
	void Render() override;
	
	//当たり判定
	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr)override;
	
private:
	//モデルデータ
	DirectX::Model*                              m_model;
	//当たり判定
	std::unique_ptr<BoxCollider>                 m_collider;
	//デバックボックス
	std::unique_ptr<DirectX::GeometricPrimitive> m_debugBox;
	DirectX::SimpleMath::Color                   m_color;
	
public:
	void SetModel(DirectX::Model * model);
};


