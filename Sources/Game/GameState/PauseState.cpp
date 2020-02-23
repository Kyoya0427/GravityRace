//======================================================
// File Name	 : PauseState.cpp
// Summary	 : ポーズステイト
// Author		 : Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "PauseState.h"
#include "GameStateManager.h"

#include <Keyboard.h>

#include <Utils\GameContext.h>


/// <summary>
/// コンストラクタ
/// </summary>
PauseState::PauseState()
	:IGameState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PauseState::~PauseState()
{
}
/// <summary>
/// イニシャライズ
/// </summary>
void PauseState::Initialize()
{
}
/// <summary>
/// アップデート
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void PauseState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
	}

	if (keyState.IsKeyDown(DirectX::Keyboard::X))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PopState();
	}
}
/// <summary>
/// レンダー
/// </summary>
void PauseState::Render(const DX::StepTimer& timer)
{
}
/// <summary>
/// ファイナライズ
/// </summary>
void PauseState::Finalize()
{
}
