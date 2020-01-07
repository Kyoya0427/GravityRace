//======================================================
// File Name	: Agravity.cpp
// Summary	: ���d�͈ړ�
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "Agravity.h"

#include <Game\Common\GameContext.h>

#include <Game\Camera\TPSCamera.h>

#include <Game\Source\DebugFont.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;
/// <summary>
/// �R���X�g���N�^
/// </summary>
Agravity::Agravity()
{
}

/// <summary>
/// �C�j�V�����C�Y
/// </summary>
/// <param name="player">�v���C���[</param>
void Agravity::Initialize(Player * player)
{
	m_player = player;
	m_count = 0;
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void Agravity::Update(float elapsedTime)
{
	elapsedTime;
	MovingProcess();
	CameraDirectionCalculation();
	AgravityModeOff();
}

/// <summary>
/// �`��
/// </summary>
void Agravity::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(600, 10, L"Agravity");
	debugFont->draw();
}


/// <summary>
/// �ړ�����
/// </summary>
void Agravity::MovingProcess()
{

	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	m_tracker.Update(mouseState);
	

	if (m_tracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::HELD)
	{
		m_count = 1;
		m_velocity.z = -0.4f;
		
	}
	if (m_tracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::UP && m_count == 1)
	{
		m_count = 0;
		m_velocity = Vector3::Zero;
	}
}

/// <summary>
/// �J�����̌����Ă�����Ɉړ�����ׂ̌v�Z
/// </summary>
void Agravity::CameraDirectionCalculation()
{
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();
	Matrix tpsCameraMat = tpsCamera->GetViewMatrix();

	Vector3 pos, scale;
	Quaternion rotation;
    tpsCameraMat.Decompose(scale,rotation,pos);

	Matrix rotMat = Matrix::CreateFromQuaternion(rotation);
	
	Vector3 vel = Vector3::Transform(m_velocity, rotMat.Invert());

	m_player->SetVelocity(vel);
}

/// <summary>
/// �d�͑������
/// </summary>
void Agravity::AgravityModeOff()
{
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();

	if (m_tracker.rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		m_player->ChangeStandingState();
		m_player->ChangeGravitation();
		m_player->SetVelocity(Vector3::Zero);
	}
}



