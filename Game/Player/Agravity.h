//======================================================
// File Name	: Agravity.h
// Summary	: 無重力移動
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
	//コンストラクタ
	Agravity();
	//初期化
	void Initialize(Player* player) override;
	//更新
	void Update(float elapsedTime) override;
	//描画
	void Render() override;

public:
	void MovingProcess();
	void CameraDirectionCalculation();
	void AgravityModeOff();

private:
	Player*									m_player;
	DirectX::SimpleMath::Vector3            m_velocity;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker                       m_tracker;
	int m_count;
};

