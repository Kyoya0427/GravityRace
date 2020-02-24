//======================================================
// File Name	: TPSCamera.cpp
// Summary	: デバッグカメラ
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "TPSCamera.h"

#include <Game\Player\Player.h>

#include <Utils\GameContext.h>
#include <Utils\ServiceLocator.h>



using namespace DirectX;
using namespace DirectX::SimpleMath;

// 定数
const float TPSCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

/// <summary>
/// コンストラクタ
/// </summary>
TPSCamera::TPSCamera()
	:GameObject(ObjectID::CAMERA)
	,m_euler()

{
	// マウスを相対モードへ変更
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::Mode::MODE_RELATIVE);

}

/// <summary>
/// デストラクタ
/// </summary>
TPSCamera::~TPSCamera()
{

}

/// <summary>
/// アップデート
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void TPSCamera::Update(const DX::StepTimer& timer)
{
	timer;
	Player* player = GameContext().Get<Player>();
	DirectX::SimpleMath::Vector3 playerPos = player->GetPosition();

	m_tracker.Update(DirectX::Mouse::Get().GetState());

	auto state = m_tracker.GetLastState();
	
	// 相対モードなら
	if (state.positionMode == DirectX::Mouse::MODE_RELATIVE)
	{
		motion(static_cast<float>(state.x),static_cast<float>(state.y));
	}
	else
	{
		if (m_tracker.leftButton == DirectX::Mouse::ButtonStateTracker::ButtonState::PRESSED)
		{
			// マウスの座標を取得
			m_prevX = state.x;
			m_prevY = state.y;
		}

		// マウスのボタンが押されていたらカメラを移動させる
		if (state.leftButton)
		{
			// マウスポインタの前回からの変位
			float dx = static_cast<float>(state.x - m_prevX);
			float dy = static_cast<float>(state.y - m_prevY);

			motion(dx, dy);
		}

		// マウスの座標を前回のとして保存
		m_prevX = state.x;
		m_prevY = state.y;
	}
	DirectX::SimpleMath::Vector3 eyepos, refpos;

	// ビュー行列を算出する
	DirectX::SimpleMath::Vector3 cameraV(0.0f, 0.0f, 13.0f);
//	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	static DirectX::SimpleMath::Vector3 sUp = DirectX::SimpleMath::Vector3::Up;
	DirectX::SimpleMath::Vector3 up = player->GetAxis();
	DirectX::SimpleMath::Vector3 cross = sUp.Cross(up);
	cross.Normalize();
	float angle = std::acosf(sUp.Dot(up) / (sUp.Length()*up.Length()));

	cameraV = DirectX::SimpleMath::Vector3::Transform(cameraV, m_rotation);
	if (cross.Length() > FLT_EPSILON) {
		sUp = DirectX::SimpleMath::Vector3::Transform(sUp, DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(cross, angle*0.2f));
	}

	//up *= DirectX::SimpleMath::Vector3::Transform(up, Matrix::CreateRotationX(player->GetAxis().x));
	//up *= DirectX::SimpleMath::Vector3::Transform(up, Matrix::CreateRotationY(player->GetAxis().y));
	//up *= DirectX::SimpleMath::Vector3::Transform(up, Matrix::CreateRotationZ(player->GetAxis().z));
	

	refpos = playerPos + DirectX::SimpleMath::Vector3(0.0f, 2.0f, 0.0f);
	eyepos = refpos + cameraV;

	eyepos += (eyepos - m_eye)* 0.03f;
	refpos += (refpos - m_target)*0.15f;
	
	m_eye = eyepos;
	m_target = refpos;

//	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, sUp);
//	DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XM_PIDIV2
}

/// <summary>
/// 描画
/// </summary>
void TPSCamera::Render(const DX::StepTimer& timer)
{
	timer;
}



void TPSCamera::HitContact(GameObject * object, RaycastHit * raycastHit)
{
	object;
	raycastHit;
}



/// <summary>
/// 行列の生成
/// </summary>
/// <param name="dx">X軸</param>
/// <param name="dy">Y軸</param>
void TPSCamera::motion(float dx, float dy)
{
	if (dx != 0.0f || dy != 0.0f)
	{
		// Ｙ軸の回転
		float angleY = dx * (DirectX::XM_PI / 180.0f);
		// Ｘ軸の回転
		float angleX = dy * (DirectX::XM_PI / 180.0f);

		m_euler.x -= angleX;
		m_euler.y -= angleY;

		m_rotation = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_euler.y, m_euler.x, m_euler.z);
	}
}


