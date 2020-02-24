//======================================================
// File Name	: Running.h
// Summary	: �W�����v����
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "IPlayer.h"

#include <Mouse.h>

class Player;

class Running :public IPlayer
{
public:
	//�R���X�g���N�^
	Running();
	//������
	void Initialize(Player* player) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render(const DX::StepTimer& timer) override;

private:
	void JumpingProcess();
	void MovingProcess();
	void ModeChangeProcess();
private:
	//�v���C���[
	Player*									                 m_player;
	//�L�[�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;
	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker                       m_tracker;
};


