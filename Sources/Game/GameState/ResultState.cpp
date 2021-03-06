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

#include <WICTextureLoader.h>

#include <Common\DeviceResources.h>

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
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Result.png", NULL, m_texture.ReleaseAndGetAddressOf());
	m_pos = DirectX::SimpleMath::Vector2(0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void ResultState::Update(float elapsedTime)
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_keyTracker.Update(keyState);

	if (m_keyTracker.IsKeyReleased(DirectX::Keyboard::Space))
	{
		using StateID = GameStateManager::GameStateID;

		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
	}
}

/// <summary>
///描画
/// </summary>
void ResultState::Render()
{
	m_spriteBatch->Begin();
	m_spriteBatch->Draw(m_texture.Get(), m_pos);
	m_spriteBatch->End();
}

/// <summary>
/// ファイナライズ
/// </summary>
void ResultState::Finalize()
{
}
