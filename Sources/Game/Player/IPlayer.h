//======================================================
// File Name	: IPlayer.h
// Summary	: プレイヤーインターフェイス
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
	//初期化
	virtual void Initialize(Player* player) = 0;
	//更新
	virtual void Update(float elapsedTime) = 0;
	//描画
	virtual void Render() = 0;

protected:
	using GravityState = Player::GravityState;
	using Contact	   = Player::Contact;
};