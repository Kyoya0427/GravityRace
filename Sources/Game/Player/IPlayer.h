//======================================================
// File Name	: IPlayer.h
// Summary	: �v���C���[�C���^�[�t�F�C�X
// Author		: Kyoya Sakamoto
//======================================================
#pragma once
#include "Player.h"

#include <Framework\StepTimer.h>

class Player;

class IPlayer
{
public:
	virtual ~IPlayer() = default;
	//������
	virtual void Initialize(Player* player) = 0;
	//�X�V
	virtual void Update(float elapsedTime) = 0;
	//�`��
	virtual void Render() = 0;

protected:
	using GravityState = Player::GravityState;
	using Contact	   = Player::Contact;
};