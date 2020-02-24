//======================================================
// File Name	: Running.h
// Summary	: ジャンプ処理
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "IPlayer.h"

#include <Mouse.h>

class Player;

class Running :public IPlayer
{
public:
	//コンストラクタ
	Running();
	//初期化
	void Initialize(Player* player) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render(const DX::StepTimer& timer) override;

private:
	void JumpingProcess();
	void MovingProcess();
	void ModeChangeProcess();
private:
	//プレイヤー
	Player*									                 m_player;
	//キートラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker                       m_tracker;
};


