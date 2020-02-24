//======================================================
// File Name	: Building.cpp
// Summary	: 地面
// Author		: Kyoya Sakamoto
//======================================================

#include "Building.h"

#include <Effects.h>




#include <Utils\GameContext.h>
#include <Framework\DeviceResources.h>

#include <Game\Collider\CollisionManager.h>
#include <Game\Collider\BoxCollider.h>

#include <Utils\Projection.h>

#include <Game\Camera\TPSCamera.h>



using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// デストラクタ
/// </summary>
/// <param name="pos">初期値</param>
Building::Building(Vector3& pos,Vector3& size)
	:GameObject(ObjectID::GROUND)
	,m_model()
{
	ID3D11DeviceContext* context = GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext();

	m_position = pos;
	m_size = size;
	m_color = Colors::Red;
	m_debugBox = GeometricPrimitive::CreateBox(context, m_size);
	m_collider = std::make_unique<BoxCollider>(this, m_size);
	GameContext().Get<CollisionManager>()->Add("Ground", m_collider.get());
}

/// <summary>
/// デストラクタ
/// </summary>
Building::~Building()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void Building::Update(const DX::StepTimer& timer)
{
	timer;

	m_collisionPos = m_position;
	m_collider->SetCollisionCenter(m_collisionPos);
	
}

/// <summary>
/// 描画
/// </summary>
void Building::Render(const DX::StepTimer& timer)
{
	ID3D11DeviceContext*   deviceContext = GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext().Get<DirectX::CommonStates>();
	Projection*  projection = GameContext().Get<Projection>();
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();

	m_scale = 0.2;

	m_world = DirectX::SimpleMath::Matrix::Identity;
	m_world *= DirectX::SimpleMath::Matrix::CreateScale(m_scale);
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	Matrix debugBoxtransMat = Matrix::CreateTranslation(m_collisionPos);
	Matrix debugBoxWorld = debugBoxtransMat;

	/*std::unique_ptr<Model> builModel;
	builModel = Model::CreateFromCMO(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/Building1.cmo", *GameContext().Get<EffectFactory>());
	m_model = builModel.get();*/
	m_model->Draw(deviceContext, *state, m_world, tpsCamera->GetViewMatrix(), projection->GetMatrix());
	
	
	m_debugBox->Draw(debugBoxWorld, tpsCamera->GetViewMatrix(), projection->GetMatrix(), m_color, nullptr, true);
}

/// <summary>
/// 当たった時の処理
/// </summary>
/// <param name="object">当たったオブジェクト</param>
void Building::HitContact(GameObject * object, RaycastHit* raycastHit)
{
	object;
	raycastHit;

}

void Building::SetModel(DirectX::Model * model)
{
	m_model = model;
}


