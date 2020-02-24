//======================================================
// File Name	: Building.h
// Summary	: �n��
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
	
	//�����蔻��
	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr)override;
	
private:
	//���f���f�[�^
	DirectX::Model*                              m_model;
	//�����蔻��
	std::unique_ptr<BoxCollider>                 m_collider;
	//�f�o�b�N�{�b�N�X
	std::unique_ptr<DirectX::GeometricPrimitive> m_debugBox;
	DirectX::SimpleMath::Color                   m_color;
	
public:
	void SetModel(DirectX::Model * model);
};


