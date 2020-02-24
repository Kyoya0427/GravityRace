//======================================================
// File Name	: Standing.h
// Summary	: 停止状態
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
	//コンストラクタ
	Standing();
	//初期化
	void Initialize(Player* player) override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render(const DX::StepTimer& timer) override;

private:
	void JumpingProcess();
	void MoveProcess();
	void ModeChangeProcess();

private:
	//プレイヤー
	Player*									                 m_player;
	//キートラッカー
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyTracker;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker                       m_tracker;
};

