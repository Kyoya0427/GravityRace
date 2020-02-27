//======================================================
// File Name	: TPSCamera.h
// Summary	: デバッグカメラ
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SimpleMath.h>
#include <Mouse.h>

#include <Framework\DeviceResources.h>
#include <Game\Object\GameObject.h>
#include <Utils\Projection.h>

// デバッグ用カメラクラス
class TPSCamera :public GameObject
{
public: // 定数

		// カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;

public: 

	// コンストラクタ
	TPSCamera();
	// デストラクタ
	~TPSCamera();

public: 
	// 更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render(const DX::StepTimer& timer) override;
	//当たり判定後の処理
	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr) override;

public: 
	// ビュー行列取得
	DirectX::SimpleMath::Matrix GetViewMatrix();    
	// デバッグカメラの位置取得
	DirectX::SimpleMath::Vector3 GetEyePosition();   
	// デバッグカメラの注視点取得
	DirectX::SimpleMath::Vector3 GetTargetPosition();
	//オイラー角を取得
	DirectX::SimpleMath::Vector3 GetEuler();
	//射影行列取得
	DirectX::SimpleMath::Matrix GetProjection();

private: 
	//回転行列の生成
	void motion(float dx, float dy);
	//射影行列生成
	void CreateProjection();

private: 
	// 前回のマウス座標
	int m_prevX, m_prevY;
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix        m_view;	
	// 視点
	DirectX::SimpleMath::Vector3       m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3       m_target;
	//オイラー角
	DirectX::SimpleMath::Vector3       m_euler;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;
	//射影行列
	std::unique_ptr<Projection>        m_projection;
};


/// <summary>
/// ビュー行列取得
/// </summary>
/// <returns></returns>
 inline DirectX::SimpleMath::Matrix TPSCamera::GetViewMatrix()
{
	 return m_view;
}


/// <summary>
/// 視点座標取得
/// </summary>
/// <returns></returns>
inline DirectX::SimpleMath::Vector3 TPSCamera::GetEyePosition()
{
	return m_eye;
}

/// <summary>
/// 注視点座標取得
/// </summary>
/// <returns></returns>
inline DirectX::SimpleMath::Vector3 TPSCamera::GetTargetPosition()
{
	return m_target;
}

/// <summary>
/// オイラー角取得
/// </summary>
/// <returns></returns>
inline DirectX::SimpleMath::Vector3 TPSCamera::GetEuler()
{
	return m_euler;
}

/// <summary>
/// 射影行列取得
/// </summary>
/// <returns></returns>
inline DirectX::SimpleMath::Matrix TPSCamera::GetProjection()
{
	return m_projection.get()->GetMatrix();
}