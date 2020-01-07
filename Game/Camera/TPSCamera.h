//======================================================
// File Name		: TPSCamera.h
// Summary		: �f�o�b�O�J����
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SimpleMath.h>
#include <Mouse.h>

#include <Game\Common\DeviceResources.h>
#include <Game\Object\GameObject.h>

// �f�o�b�O�p�J�����N���X
class TPSCamera :public GameObject
{
public: // �萔

		// �J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

public: // ��{

	// �R���X�g���N�^
	TPSCamera();
	// �f�X�g���N�^
	~TPSCamera();

public: // ��{����

	// �X�V

	void Update(float elapsedTime) override;
	void Render() override;

	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr) override;
public: // �A�N�Z�b�T

	// �r���[�s��擾
	DirectX::SimpleMath::Matrix GetViewMatrix()      { return m_view; }
	// �f�o�b�O�J�����̈ʒu�擾
	DirectX::SimpleMath::Vector3 GetEyePosition()    { return m_eye; }
	// �f�o�b�O�J�����̒����_�擾
	DirectX::SimpleMath::Vector3 GetTargetPosition() { return m_target; }
	//�I�C���[�p���擾
	DirectX::SimpleMath::Vector3 GetEuler() { return m_euler; }
	
private: // �T�u����
	void motion(float dx, float dy);

private: // �ϐ�

	// �O��̃}�E�X���W
	int m_prevX, m_prevY;
	// �������ꂽ�r���[�s��
	DirectX::SimpleMath::Matrix m_view;	
	// ���_
	DirectX::SimpleMath::Vector3 m_eye;
	// �����_
	DirectX::SimpleMath::Vector3 m_target;
	//�I�C���[�p
	DirectX::SimpleMath::Vector3 m_euler;
	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_tracker;
};
