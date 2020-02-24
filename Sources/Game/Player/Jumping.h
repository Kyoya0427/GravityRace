//======================================================
// File Name	: Jumping.h
// Summary	: ジャンプ処理
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
	//コンストラクタ
	Jumping();
	//初期化
	void Initialize(Player* player) override;
	//更新
	void Update(float elapsedTime) override;
	//描画
	void Render() override;

public:
	void MovingProcess();
	void ModeChangeProcess();
private:
	Player*									m_player;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker                       m_tracker;
};

