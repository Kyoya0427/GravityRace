//======================================================
// File Name	: Ground.cpp
// Summary	: �n��
// Author		: Kyoya Sakamoto
//======================================================

#include "Ground.h"

#include <Effects.h>

#include <Game\Source\DebugFont.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Collider\CollisionManager.h>
#include <Game\Collider\BoxCollider.h>

#include <Game\Common\Projection.h>

#include <Game\Camera\TPSCamera.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <param name="pos">�����l</param>
Ground::Ground(Vector3& pos)
	:GameObject(ObjectID::GROUND)	
{
	DX::DeviceResources* deviceResources = GameContext().Get<DX::DeviceResources>();
	ID3D11Device*          device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

	m_position = pos;

	m_size = Vector3(239.2f, 6.5f, 274.7f);
	
	m_color = Colors::Red;



	m_model = Model::CreateFromCMO(device, L"Resources/Models/Ground.cmo", *GameContext().Get<EffectFactory>());
	
	m_debugBox = GeometricPrimitive::CreateBox(context, m_size);
	m_collider = std::make_unique<BoxCollider>(this, m_size);
	GameContext().Get<CollisionManager>()->Add("Ground", m_collider.get());
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Ground::~Ground()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void Ground::Update(float elapsedTime)
{
	elapsedTime;

	m_collisionPos = m_position;
	m_collider->SetCollisionCenter(m_collisionPos);
}

/// <summary>
/// �`��
/// </summary>
void Ground::Render()
{
	DX::DeviceResources* deviceResources = GameContext().Get<DX::DeviceResources>();
	ID3D11DeviceContext*   deviceContext = deviceResources->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext().Get<DirectX::CommonStates>();
	Projection*  projection = GameContext().Get<Projection>();
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();

	m_scale = 0.05;

	m_world = DirectX::SimpleMath::Matrix::Identity;
	m_world *= DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	Matrix debugBoxtransMat = Matrix::CreateTranslation(m_collisionPos);
	Matrix debugBoxWorld = debugBoxtransMat;

	m_model->Draw(deviceContext, *state, m_world, tpsCamera->GetViewMatrix(), projection->GetMatrix());
	m_debugBox->Draw(debugBoxWorld, tpsCamera->GetViewMatrix(), projection->GetMatrix(), m_color, nullptr, true);

	
	
}

/// <summary>
/// �����������̏���
/// </summary>
/// <param name="object">���������I�u�W�F�N�g</param>
void Ground::HitContact(GameObject * object, RaycastHit* raycastHit)
{
	object;
	raycastHit;
}




