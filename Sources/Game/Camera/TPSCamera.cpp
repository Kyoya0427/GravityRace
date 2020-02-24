//======================================================
// File Name	: TPSCamera.cpp
// Summary	: �f�o�b�O�J����
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "TPSCamera.h"

#include <Game\Player\Player.h>

#include <Utils\GameContext.h>
#include <Utils\ServiceLocator.h>



using namespace DirectX;
using namespace DirectX::SimpleMath;

// �萔
const float TPSCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

/// <summary>
/// �R���X�g���N�^
/// </summary>
TPSCamera::TPSCamera()
	:GameObject(ObjectID::CAMERA)
	,m_euler()

{
	// �}�E�X�𑊑΃��[�h�֕ύX
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::Mode::MODE_RELATIVE);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TPSCamera::~TPSCamera()
{

}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void TPSCamera::Update(const DX::StepTimer& timer)
{
	timer;
	Player* player = GameContext().Get<Player>();
	DirectX::SimpleMath::Vector3 playerPos = player->GetPosition();

	m_tracker.Update(DirectX::Mouse::Get().GetState());

	auto state = m_tracker.GetLastState();
	
	// ���΃��[�h�Ȃ�
	if (state.positionMode == DirectX::Mouse::MODE_RELATIVE)
	{
		motion(static_cast<float>(state.x),static_cast<float>(state.y));
	}
	else
	{
		if (m_tracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
		{
			// �}�E�X�̍��W���擾
			m_prevX = state.x;
			m_prevY = state.y;
		}

		// �}�E�X�̃{�^����������Ă�����J�������ړ�������
		if (state.leftButton)
		{
			// �}�E�X�|�C���^�̑O�񂩂�̕ψ�
			float dx = static_cast<float>(state.x - m_prevX);
			float dy = static_cast<float>(state.y - m_prevY);

			motion(dx, dy);
		}

		// �}�E�X�̍��W��O��̂Ƃ��ĕۑ�
		m_prevX = state.x;
		m_prevY = state.y;
	}
	DirectX::SimpleMath::Vector3 eyepos, refpos;

	// �r���[�s����Z�o����
	DirectX::SimpleMath::Vector3 cameraV(0.0f, 0.0f, 13.0f);
//	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	static DirectX::SimpleMath::Vector3 sUp = DirectX::SimpleMath::Vector3::Up;
	DirectX::SimpleMath::Vector3 up = player->GetAxis();
	DirectX::SimpleMath::Vector3 cross = sUp.Cross(up);
	cross.Normalize();
	float angle = std::acosf(sUp.Dot(up) / (sUp.Length()*up.Length()));

	cameraV = DirectX::SimpleMath::Vector3::Transform(cameraV, m_rotation);
	if (cross.Length() > FLT_EPSILON) {
		sUp = DirectX::SimpleMath::Vector3::Transform(sUp, DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(cross, angle*0.2f));
	}

	//up *= DirectX::SimpleMath::Vector3::Transform(up, Matrix::CreateRotationX(player->GetAxis().x));
	//up *= DirectX::SimpleMath::Vector3::Transform(up, Matrix::CreateRotationY(player->GetAxis().y));
	//up *= DirectX::SimpleMath::Vector3::Transform(up, Matrix::CreateRotationZ(player->GetAxis().z));
	

	refpos = playerPos + DirectX::SimpleMath::Vector3(0.0f, 2.0f, 0.0f);
	eyepos = refpos + cameraV;

	eyepos += (eyepos - m_eye)* 0.03f;
	refpos += (refpos - m_target)*0.15f;
	
	m_eye = eyepos;
	m_target = refpos;

//	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, sUp);
//	DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XM_PIDIV2
}

/// <summary>
/// �`��
/// </summary>
void TPSCamera::Render(const DX::StepTimer& timer)
{
	timer;
}



void TPSCamera::HitContact(GameObject * object, RaycastHit * raycastHit)
{
	object;
	raycastHit;
}



/// <summary>
/// �s��̐���
/// </summary>
/// <param name="dx">X��</param>
/// <param name="dy">Y��</param>
void TPSCamera::motion(float dx, float dy)
{
	if (dx != 0.0f || dy != 0.0f)
	{
		// �x���̉�]
		float angleY = dx * (DirectX::XM_PI / 180.0f);
		// �w���̉�]
		float angleX = dy * (DirectX::XM_PI / 180.0f);

		m_euler.x -= angleX;
		m_euler.y -= angleY;

		m_rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_euler.y, m_euler.x, m_euler.z);
	}
}


