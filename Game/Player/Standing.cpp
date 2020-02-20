//======================================================
// File Name	: Standing.cpp
// Summary	: ��~���
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>
#include <Game\Source\DebugFont.h>

#include <Game\Common\GameContext.h>

#include <Game\Camera\TPSCamera.h>

#include "Standing.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Standing::Standing()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="player">�v���C���[</param>
void Standing::Initialize(Player * player)
{
	m_player = player;
	m_keyTracker = make_unique<Keyboard::KeyboardStateTracker>();
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void Standing::Update(float elapsedTime)
{
	elapsedTime;
	m_player->ChangeGravitation();
	MoveProcess();
	
	JumpingProcess();

	ModeChangeProcess();
}

/// <summary>
/// �`��
/// </summary>
void Standing::Render()
{
}

/// <summary>
/// �W�����v����
/// </summary>
void Standing::JumpingProcess()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Space))
	{
		m_player->SetVelY(1.5f);
		m_player->ChangeJumpingState();
	}
}

/// <summary>
/// �ړ�����
/// </summary>
void Standing::MoveProcess()
{
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	DirectX::SimpleMath::Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, tpsCamera->GetEuler().y);
	Vector3 vel = Vector3::Zero;

	if (m_player->GetContact() == Contact::HIT_CONTACT)
	{
		if (keyState.IsKeyDown(DirectX::Keyboard::Keys::A))
		{
			vel.x = -0.2;
			m_player->SetVelocity(Vector3::Transform(vel, rot));
			m_player->ChangeRunningState();
		}
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::D))
		{
			vel.x = 0.2;
			m_player->SetVelocity(Vector3::Transform(vel, rot));
			m_player->ChangeRunningState();
		}
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::W))
		{
			vel.z = -0.2;
			m_player->SetVelocity(Vector3::Transform(vel, rot));
			m_player->ChangeRunningState();

		}
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::S))
		{
			vel.z = 0.2;
			m_player->SetVelocity(Vector3::Transform(vel, rot));
			m_player->ChangeRunningState();
		}
		else
		{
			m_player->SetVelocity(Vector3::Zero);
		}
	}
}

/// <summary>
/// ���V���[�h�ڍs����
/// </summary>
void Standing::ModeChangeProcess()
{
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	m_tracker.Update(mouseState);

	if (m_tracker.rightButton == DirectX::Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		m_player->SetVelocity(Vector3::Zero);
		m_player->ChangeAgravity();
		m_player->ChangeFloatingState();
	}
}
