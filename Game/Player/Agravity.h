//======================================================
// File Name	: Agravity.h
// Summary	: ���d�͈ړ�
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Keyboard.h>
#include <Mouse.h>

#include "IPlayer.h"
#include "Player.h"

class Player;


class Agravity :public IPlayer
{
public:
	//�R���X�g���N�^
	Agravity();
	//������
	void Initialize(Player* player) override;
	//�X�V
	void Update(float elapsedTime) override;
	//�`��
	void Render() override;

public:
	void MovingProcess();
	void CameraDirectionCalculation();
	void AgravityModeOff();

private:
	Player*									m_player;
	DirectX::SimpleMath::Vector3            m_velocity;
	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker                       m_tracker;
	int m_count;
};

