//======================================================
// File Name	: Running.cpp
// Summary	: �W�����v����
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "Running.h"



#include <Utils\Utilities.h>
#include <Utils\GameContext.h>
#include <Game\Camera\TPSCamera.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Running::Running()
{
}

/// <summary>
///������ 
/// </summary>
/// <param name="player">�v���C���[</param>
void Running::Initialize(Player * player)
{
	m_player = player;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void Running::Update(const DX::StepTimer& timer)
{
	timer;
	m_player->ChangeGravitation();
	MovingProcess();

	JumpingProcess();

	ModeChangeProcess();
}

/// <summary>
/// �`��
/// </summary>
void Running::Render(const DX::StepTimer& timer)
{
}

/// <summary>
/// �W�����v����
/// </summary>
void Running::JumpingProcess()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Space))
	{
		m_player->SetVelY(1.5f);
		m_player->ChangeJumpingState();
	}
}

/// <summary>
///�ړ����� 
/// </summary>
void Running::MovingProcess()
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
			m_player->ChangeStandingState();
		}
	}
}

/// <summary>
/// ���[�h�ύX
/// </summary>
void Running::ModeChangeProcess()
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



