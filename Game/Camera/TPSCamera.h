//======================================================
// File Name		: TPSCamera.h
// Summary		: デバッグカメラ
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SimpleMath.h>
#include <Mouse.h>

#include <Game\Common\DeviceResources.h>
#include <Game\Object\GameObject.h>

// デバッグ用カメラクラス
class TPSCamera :public GameObject
{
public: // 定数

		// カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;

public: // 基本

	// コンストラクタ
	TPSCamera();
	// デストラクタ
	~TPSCamera();

public: // 基本処理

	// 更新

	void Update(float elapsedTime) override;
	void Render() override;

	void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr) override;
public: // アクセッサ

	// ビュー行列取得
	DirectX::SimpleMath::Matrix GetViewMatrix()      { return m_view; }
	// デバッグカメラの位置取得
	DirectX::SimpleMath::Vector3 GetEyePosition()    { return m_eye; }
	// デバッグカメラの注視点取得
	DirectX::SimpleMath::Vector3 GetTargetPosition() { return m_target; }
	//オイラー角を取得
	DirectX::SimpleMath::Vector3 GetEuler() { return m_euler; }
	
private: // サブ処理
	void motion(float dx, float dy);

private: // 変数

	// 前回のマウス座標
	int m_prevX, m_prevY;
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;	
	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	//オイラー角
	DirectX::SimpleMath::Vector3 m_euler;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;
};
