//======================================================
// File Name	: Jumping.h
// Summary	: �W�����v����
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "IPlayer.h"

#include <Mouse.h>

#include "Player.h"


class Player;


class Jumping :public IPlayer
{
public:
	//�R���X�g���N�^
	Jumping();
	//������
	void Initialize(Player* player) override;
	//�X�V
	void Update(float elapsedTime) override;
	//�`��
	void Render() override;

public:
	void MovingProcess();
	void ModeChangeProcess();
private:
	Player*									m_player;
	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker                       m_tracker;
};

