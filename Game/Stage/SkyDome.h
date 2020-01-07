//======================================================
// File Name	: SkyDome.h
// Summary	: スカイドーム
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
	void Update(float elapsedTime) override;
	void Render() override;

	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr) override;

private:
	//モデルデータ
	std::unique_ptr<DirectX::Model> m_model;
};

