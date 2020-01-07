//======================================================
// File Name	: Agravity.cpp
// Summary	: 無重力移動
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "Agravity.h"

#include <Game\Common\GameContext.h>

#include <Game\Camera\TPSCamera.h>

#include <Game\Source\DebugFont.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace std;
/// <summary>
/// コンストラクタ
/// </summary>
Agravity::Agravity()
{
}

/// <summary>
/// イニシャライズ
/// </summary>
/// <param name="player">プレイヤー</param>
void Agravity::Initialize(Player * player)
{
	m_player = player;
	m_count = 0;
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void Agravity::Update(float elapsedTime)
{
	elapsedTime;
	MovingProcess();
	CameraDirectionCalculation();
	AgravityModeOff();
}

/// <summary>
/// 描画
/// </summary>
void Agravity::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(600, 10, L"Agravity");
	debugFont->draw();
}


/// <summary>
/// 移動処理
/// </summary>
void Agravity::MovingProcess()
{

	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	m_tracker.Update(mouseState);
	

	if (m_tracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::HELD)
	{
		m_count = 1;
		m_velocity.z = -0.4f;
		
	}
	if (m_tracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::UP && m_count == 1)
	{
		m_count = 0;
		m_velocity = Vector3::Zero;
	}
}

/// <summary>
/// カメラの向いてる方向に移動する為の計算
/// </summary>
void Agravity::CameraDirectionCalculation()
{
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();
	Matrix tpsCameraMat = tpsCamera->GetViewMatrix();

	Vector3 pos, scale;
	Quaternion rotation;
    tpsCameraMat.Decompose(scale,rotation,pos);

	Matrix rotMat = Matrix::CreateFromQuaternion(rotation);
	
	Vector3 vel = Vector3::Transform(m_velocity, rotMat.Invert());

	m_player->SetVelocity(vel);
}

/// <summary>
/// 重力操作解除
/// </summary>
void Agravity::AgravityModeOff()
{
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();

	if (m_tracker.rightButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		m_player->ChangeStandingState();
		m_player->ChangeGravitation();
		m_player->SetVelocity(Vector3::Zero);
	}
}



