//======================================================
// File Name	: Standing.h
// Summary	: ��~���
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "IPlayer.h"

#include <Keyboard.h>
#include <Mouse.h>

class Player;

class Standing :public IPlayer
{
public:
	//�R���X�g���N�^
	Standing();
	//������
	void Initialize(Player* player) override;
	//�X�V
	void Update(float elapsedTime) override;
	//�`��
	void Render() override;

private:
	void JumpingProcess();
	void MoveProcess();
	void ModeChangeProcess();

private:
	//�v���C���[
	Player*									                 m_player;
	//�L�[�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;
	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker                       m_tracker;
};

