//======================================================
// File Name	: TitleState.cpp
// Summary	: タイトルステイト
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "TitleState.h"

#include <Game\Source\DebugFont.h>

#include <Game\Common\GameContext.h>

#include "GameStateManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
TitleState::TitleState()
	:IGameState()
	, m_count(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
TitleState::~TitleState()
{
}

/// <summary>
/// イニシャライズ
/// </summary>
void TitleState::Initialize()
{
	m_count = 0.0f;
}

/// <summary>
///アップデート 
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void TitleState::Update(float elapsedTime)
{
	
	m_count += elapsedTime;

	if (m_count > 3)
	{
		using StateID = GameStateManager::GameStateID;

		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::PLAY_STATE);
		m_count = 0.0;
	}

}

/// <summary>
/// 描画
/// </summary>
void TitleState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"TitleState");
	debugFont->draw();
	debugFont->print(10, 40, L"%.2f / 3",m_count);
	debugFont->draw();
}

/// <summary>
/// ファイナライズ
/// </summary>
void TitleState::Finalize()
{
}
