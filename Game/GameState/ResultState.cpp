//======================================================
// File Name	: ResultState.cpp
// Summary	: リザルトステイト
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "ResultState.h"

#include <Game\Source\DebugFont.h>

#include <Game\Common\GameContext.h>

#include "GameStateManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultState::ResultState()
	:IGameState()
	, m_count(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
ResultState::~ResultState()
{
}

/// <summary>
/// イニシャライズ
/// </summary>
void ResultState::Initialize()
{
	m_count = 0.0f;
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void ResultState::Update(float elapsedTime)
{
	
	m_count += elapsedTime;

	if (m_count > 3)
	{
		using StateID = GameStateManager::GameStateID;

		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
		m_count = 0.0f;
	}
}

/// <summary>
///描画
/// </summary>
void ResultState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"ResultState");
	debugFont->draw();
	debugFont->print(10, 40, L"%.2f / 3", m_count);
	debugFont->draw();
}

/// <summary>
/// ファイナライズ
/// </summary>
void ResultState::Finalize()
{
}
