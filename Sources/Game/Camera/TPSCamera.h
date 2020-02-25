//======================================================
// File Name	: TPSCamera.h
// Summary	: �f�o�b�O�J����
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SimpleMath.h>
#include <Mouse.h>

#include <Framework\DeviceResources.h>
#include <Game\Object\GameObject.h>
#include <Utils\Projection.h>

// �f�o�b�O�p�J�����N���X
class TPSCamera :public GameObject
{
public: // �萔

		// �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

public: 

	// �R���X�g���N�^
	TPSCamera();
	// �f�X�g���N�^
	~TPSCamera();

public: 
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render(const DX::StepTimer& timer) override;
	//�����蔻���̏���
	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr) override;

public: 
	// �r���[�s��擾
	DirectX::SimpleMath::Matrix GetViewMatrix();    
	// �f�o�b�O�J�����̈ʒu�擾
	DirectX::SimpleMath::Vector3 GetEyePosition();   
	// �f�o�b�O�J�����̒����_�擾
	DirectX::SimpleMath::Vector3 GetTargetPosition();
	//�I�C���[�p���擾
	DirectX::SimpleMath::Vector3 GetEuler();
	//�ˉe�s��擾
	Projection* GetProjection();

private: 
	//��]�s��̐���
	void motion(float dx, float dy);
	//�ˉe�s�񐶐�
	void CreateProjection();

private: 
	// �O��̃}�E�X���W
	int m_prevX, m_prevY;
	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix        m_view;	
	// ���_
	DirectX::SimpleMath::Vector3       m_eye;
	// �����_
	DirectX::SimpleMath::Vector3       m_target;
	//�I�C���[�p
	DirectX::SimpleMath::Vector3       m_euler;
	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_tracker;
	//�ˉe�s��
	std::unique_ptr<Projection>        m_projection;
};


/// <summary>
/// �r���[�s��擾
/// </summary>
/// <returns></returns>
DirectX::SimpleMath::Matrix TPSCamera::GetViewMatrix()
{
	return m_view;
}

/// <summary>
/// ���_���W�擾
/// </summary>
/// <returns></returns>
inline DirectX::SimpleMath::Vector3 TPSCamera::GetEyePosition()
{
	return m_eye;
}

/// <summary>
/// �����_���W�擾
/// </summary>
/// <returns></returns>
inline DirectX::SimpleMath::Vector3 TPSCamera::GetTargetPosition()
{
	return m_target;
}

/// <summary>
/// �I�C���[�p�擾
/// </summary>
/// <returns></returns>
inline DirectX::SimpleMath::Vector3 TPSCamera::GetEuler()
{
	return m_euler;
}

/// <summary>
/// �ˉe�s��擾
/// </summary>
/// <returns></returns>
inline Projection* TPSCamera::GetProjection()
{
	return m_projection.get();
}