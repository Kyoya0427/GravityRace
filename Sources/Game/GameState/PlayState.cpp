//======================================================
// File Name	: PlayState.h
// Summary	: プレイステイト
// Author		: Kyoya Sakamoto
//======================================================
#include "PlayState.h"
#include "GameStateManager.h"

#include <Keyboard.h>
#include <Effects.h>
#include <SimpleMath.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
PlayState::PlayState()
	:IGameState()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayState::~PlayState()
{

}

/// <summary>
/// 初期化
/// </summary>
void PlayState::Initialize()
{

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void PlayState::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer"></param>
void PlayState::Render(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// 終了
/// </summary>
void PlayState::Finalize()
{

}
