//======================================================
// File Name	: Jumping.cpp
// Summary	: ジャンプ処理
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "Jumping.h"

#include <Game\Source\DebugFont.h>
#include <Game\Common\Utilities.h>
#include <Game\Common\GameContext.h>
#include <Game\Camera\TPSCamera.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;

/// <summary>
/// コンストラクタ
/// </summary>
Jumping::Jumping()
{
}

/// <summary>
/// イニシャライズ
/// </summary>
/// <param name="player">プレイヤー</param>
void Jumping::Initialize(Player * player)
{
	m_player = player;
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void Jumping::Update(float elapsedTime)
{
	elapsedTime;
	m_player->ChangeGravitation();
	MovingProcess();
	ModeChangeProcess();
}

/// <summary>
/// 描画
/// </summary>
void Jumping::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(600, 10, L"Jumping");
	debugFont->draw();
}

/// <summary>
/// 移動処理
/// </summary>
void Jumping::MovingProcess()
{
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	DirectX::SimpleMath::Quaternion rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, tpsCamera->GetEuler().y);
	Vector3 vel = Vector3::Zero;

	if (m_player->GetContact() == Contact::HIT_CONTACT)
	{
		if (keyState.IsKeyDown(DirectX::Keyboard::Keys::A))
		{
			vel.x = -0.2;
			m_player->SetVelocity(Vector3::Transform(vel, rot));
			m_player->ChangeRunningState();
		}
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::D))
		{
			vel.x = 0.2;
			m_player->SetVelocity(Vector3::Transform(vel, rot));
			m_player->ChangeRunningState();

		}
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::W))
		{
			vel.z = -0.2;
			m_player->SetVelocity(Vector3::Transform(vel, rot));
			m_player->ChangeRunningState();

		}
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::S))
		{
			vel.z = 0.2;
			m_player->SetVelocity(Vector3::Transform(vel, rot));
			m_player->ChangeRunningState();
		}
		else
		{
			m_player->SetVelocity(Vector3::Zero);
			m_player->ChangeStandingState();
		}
	}
}

/// <summary>
/// モード変更
/// </summary>
void Jumping::ModeChangeProcess()
{
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	m_tracker.Update(mouseState);

	if (m_tracker.rightButton == DirectX::Mouse::ButtonStateTracker::ButtonState::RELEASED)
	{
		m_player->SetVelocity(Vector3::Zero);
		m_player->ChangeAgravity();
		m_player->ChangeFloatingState();
	}
}
