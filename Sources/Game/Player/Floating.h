//======================================================
// File Name	: Floating.h
// Summary	: �W�����v����
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "IPlayer.h"

#include <Mouse.h>

#include "Player.h"


class Player;


class Floating :public IPlayer
{
public:
	//�R���X�g���N�^
	Floating();
	//������
	void Initialize(Player* player) override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render(const DX::StepTimer& timer) override;

private:
	Player*									                 m_player;
	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker                       m_tracker;

	float                                                    m_speed;
	int                                                      m_count;
};