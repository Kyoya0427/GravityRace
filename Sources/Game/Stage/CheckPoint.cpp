//======================================================
// File Name	: CheckPoint.cpp
// Summary	:チェックポイント
// Author		: Kyoya Sakamoto
//======================================================
#include "CheckPoint.h"



#include <Utils\GameContext.h>
#include <Framework\DeviceResources.h>

#include <Game\Collider\CollisionManager.h>
#include <Game\Collider\BoxCollider.h>

#include <Utils\Projection.h>

#include <Game\Camera\TPSCamera.h>

#include <Game\GameState\GameStateManager.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

static bool check = true;

CheckPoint::CheckPoint(DirectX::SimpleMath::Vector3 & pos)
	:GameObject(ObjectID::CHECKPOINT)
{
	DX::DeviceResources* deviceResources = GameContext().Get<DX::DeviceResources>();
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

	m_position = pos;
	m_size = Vector3(2.0f,2.0f,2.0f);
	m_color = Colors::Blue;

	m_model = GeometricPrimitive::CreateBox(context, m_size); 
	m_collider = std::make_unique<BoxCollider>(this, m_size);
	GameContext().Get<CollisionManager>()->Add("Ground", m_collider.get());

	check = true;
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::Update(float elapsedTime)
{
	elapsedTime;
	m_collisionPos = m_position;
	m_collider->SetCollisionCenter(m_collisionPos);
}

void CheckPoint::Render()
{
	Projection*  projection = GameContext().Get<Projection>();
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();

	Matrix Mat = Matrix::CreateTranslation(m_position);
	Matrix world = Mat;

	if (check)
	{
		m_model->Draw(world, tpsCamera->GetViewMatrix(), projection->GetMatrix(), m_color, nullptr, false);
	}
	else
	{
		using StateID = GameStateManager::GameStateID;

		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::RESULT_STATE);
	}
}

void CheckPoint::HitContact(GameObject * object, RaycastHit * raycastHit)
{
	object;
	raycastHit;
	check = false;
}
