//======================================================
// File Name	: Floating.h
// Summary	: ジャンプ処理
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
	//コンストラクタ
	Floating();
	//初期化
	void Initialize(Player* player) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render(const DX::StepTimer& timer) override;

private:
	Player*									                 m_player;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker                       m_tracker;

	float                                                    m_speed;
	int                                                      m_count;
};