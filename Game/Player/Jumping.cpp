//======================================================
// File Name	: Jumping.cpp
// Summary	: �W�����v����
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "Jumping.h"

#include <Game\Source\DebugFont.h>
#include <Game\Common\Utilities.h>
#include <Game\Common\GameContext.h>
#include <Game\Camera\TPSCamera.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Jumping::Jumping()
{
}

/// <summary>
/// �C�j�V�����C�Y
/// </summary>
/// <param name="player">�v���C���[</param>
void Jumping::Initialize(Player * player)
{
	m_player = player;
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void Jumping::Update(float elapsedTime)
{
	elapsedTime;
	m_player->ChangeGravitation();
	MovingProcess();
	ModeChangeProcess();
}

/// <summary>
/// �`��
/// </summary>
void Jumping::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(600, 10, L"Jumping");
	debugFont->draw();
}

/// <summary>
/// �ړ�����
/// </summary>
void Jumping::MovingProcess()
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
void Jumping::ModeChangeProcess()
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
