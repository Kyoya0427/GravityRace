//======================================================
// File Name	: Player.cpp
// Summary	: �v���C���[�}�l�W���[
// Author		: Kyoya Sakamoto
//======================================================

#include "Player.h"
#include "Standing.h"
#include "Running.h"
#include "Jumping.h"
#include "Floating.h"
#include "Agravity.h"

#include <Effects.h>



#include <Utils\GameContext.h>
#include <Utils\Projection.h>

#include <Game\Collider\CollisionManager.h>
#include <Game\Collider\MoveBoxCollider.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	:GameObject(ObjectID::PLAYER)
{
	DX::DeviceResources* deviceResources = GameContext().Get<DX::DeviceResources>();
	ID3D11Device*        device          = deviceResources->GetD3DDevice();

	m_model = Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *GameContext().Get<EffectFactory>());

	
	m_position = Vector3(-116.0f, 5.0f, 134.0f);
	m_size = Vector3(2.0f, 2.0f, 2.0f);
	m_gravity = 0.0f;
	m_energy = 5.0f;
	//�X�e�C�g���C�N
	m_standing = std::make_unique<Standing>();
	m_running = std::make_unique<Running>();
	m_jumping = std::make_unique<Jumping>();
	m_floating = std::make_unique<Floating>();
	m_agravity = std::make_unique<Agravity>();
	//�X�e�C�g������
	m_standing->Initialize(this);
	m_running->Initialize(this);
	m_jumping->Initialize(this);
	m_floating->Initialize(this);
	m_agravity->Initialize(this);


	Vector3 direction = Vector3(MOVE_SPEED, MOVE_SPEED, MOVE_SPEED);
	m_collider = std::make_unique<MoveBoxCollider>(this, m_size);
	m_collider->SetPosition(m_position);
	GameContext().Get<CollisionManager>()->Add("Player", m_collider.get());

	ChangeGravitation();
	
	ChangeStandingState();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{

}

/// <summary>
///	�X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void Player::Update(const DX::StepTimer& timer)
{
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();

	m_position += m_velocity;

	//�d��
	m_gravity = -0.08;
	if (m_isGravityState == GravityState::AGRAVITY)
	{
		//m_energy -= elapsedTime;
		//SetVelocity(GetVelosity() + (m_raycastHit.normNear * m_gravity));
	}
	else if(m_isGravityState == GravityState::GRAVITATION)
	{
		//m_energy += elapsedTime;
		SetVelY(GetVelosity().y + m_gravity);
	}

	if (m_energy <= 0.0f)
	{
		ChangeStandingState();
		m_energy = 0.0f;
	}

	if (m_energy >= 5.0f)
	{
		m_energy = 5.0f;
	}

	m_player->Update(timer);

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (GetPosition().y <= - 100.0f)
	{
		SetPosition(Vector3(-116.0f, 5.0f, 134.0f));
		SetVelocity(Vector3::Zero);
	}

	m_rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, tpsCamera->GetEuler().y);
	

	m_collider->SetPosition(m_position);
	m_collider->SetVelocity(m_velocity);

	
	ChangeNoContact();
	
}

/// <summary>
/// �`��
/// </summary>
void Player::Render(const DX::StepTimer& timer)
{
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();
	DX::DeviceResources* deviceResources = GameContext().Get<DX::DeviceResources>();
	ID3D11DeviceContext*   deviceContext = deviceResources->GetD3DDeviceContext();
	DirectX::CommonStates* state         = GameContext().Get<DirectX::CommonStates>();

	m_scale = 0.05;

	Matrix scalemat = Matrix::CreateScale(m_scale);
	Matrix rotMat = Matrix::CreateFromQuaternion(m_rotation) ;
	
	
	
	Matrix transMat = Matrix::CreateTranslation(m_position);
	m_world = scalemat * rotMat * transMat;

	m_model->Draw(deviceContext, *state, m_world, tpsCamera->GetViewMatrix(), tpsCamera->GetProjection());

	m_player->Render(timer);

}


/// <summary>
/// �Փ˂���
/// </summary>
/// <param name="object"></param>
/// <param name="raycastHit"></param>
void Player::HitContact(GameObject * object, RaycastHit* raycastHit)
{
	if (object->GetTag() == ObjectID::GROUND)
	{
		m_raycastHit = *raycastHit;
		ChangeHitContact();

		if (raycastHit->normNear.x != 0.0f)
			m_velocity.x = 0.0f;
		if (raycastHit->normNear.y != 0.0f)
			m_velocity.y = 0.0f;
		if (raycastHit->normNear.z != 0.0f)
			m_velocity.z = 0.0f;

		if (raycastHit->normNear.y > 0.0f)
		{
			ChangeStandingState();
			ChangeGravitation();
		}
	}
}




