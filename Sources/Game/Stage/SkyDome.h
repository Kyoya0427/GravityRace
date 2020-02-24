//======================================================
// File Name	: SkyDome.h
// Summary	: �X�J�C�h�[��
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Model.h>
#include <GeometricPrimitive.h>
#include <Game\Object\GameObject.h>


class SkyDome : public GameObject
{
public:
	SkyDome();
	~SkyDome();

public:
	void Update(const DX::StepTimer& timer) override;
	void Render(const DX::StepTimer& timer) override;

	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr) override;

private:
	//���f���f�[�^
	std::unique_ptr<DirectX::Model> m_model;
};

