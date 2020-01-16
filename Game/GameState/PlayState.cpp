//======================================================
// File Name	 : play.cpp
// Summary	 : プレイステイト
// Author		 : Kyoya Sakamoto
//======================================================
//#include <pch.h>

#include "PlayState.h"
#include "GameStateManager.h"

#include <Keyboard.h>
#include <Effects.h>

#include <Game\Source\DebugFont.h>

#include <Game\Common\DeviceResources.h>
#include <Game\Common\GameContext.h>
#include <Game\Common\Projection.h>
#include <Game\Common\StepTimer.h>

#include <Game\Object\GameObjectManager.h>

#include <Game\Collider\CollisionManager.h>

#include <Game\Source\GridFloor.h>

#include <Game\Camera\TPSCamera.h>

#include <Game\Player\Player.h>

#include <Game\Stage\Ground.h>
#include <Game\Stage\SkyDome.h>
#include <Game\Stage\CheckPoint.h>
#include <Game\Stage\Building.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
PlayState::PlayState()
	:IGameState()
	, m_effectManager(nullptr)
	,m_count(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayState::~PlayState()
{
	if (m_effectManager != nullptr) {
		m_effectManager->Lost();
		delete m_effectManager;
		m_effectManager = nullptr;
	}
}

/// <summary>
/// イニシャライズ
/// </summary>
void PlayState::Initialize()
{
	//ゲームコンテキスト
	ID3D11Device* device = GameContext().Get<DX::DeviceResources>()->GetD3DDevice();

	//ゲームオブジェクトマネジャー
	m_gameObjectManager = std::make_unique<GameObjectManager>();
	GameContext().Register<GameObjectManager>(m_gameObjectManager.get());

	//コリジョンマネージャー
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext().Register<CollisionManager>(m_collisionManager.get());

	//エフェクトファクトリー設定
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	factory->SetDirectory(L"Resources/Models");
	GameContext().Register<EffectFactory>(factory);

	//カメラ作成
	std::unique_ptr<TPSCamera> tpsCamera = std::make_unique<TPSCamera>();
	GameContext().Register<TPSCamera>(tpsCamera.get());
	
	//プレイヤー作成
	std::unique_ptr<Player> player = std::make_unique<Player>();
	GameContext().Register<Player>(player.get());

	////地面作成
	std::unique_ptr<Ground> ground[1];
	ground[0] = std::make_unique<Ground>(Vector3(  0.0f, 0.0f,   0.0f));

	m_effectManager = new EnergyEffectManager();
	m_effectManager->Create(GameContext().Get<DX::DeviceResources>(), L"Resources\\Textures\\energy.png", 1);
	m_effectManager->InitializeCorn(5, Vector3(0, 0, 0), Vector3(0, 1, 0));
	m_effectManager->SetRenderState(tpsCamera->GetPosition() + tpsCamera->GetEyePosition(), tpsCamera->GetViewMatrix() , GameContext().Get<Projection>()->GetMatrix());

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//stage
	std::unique_ptr<CheckPoint> checkPoint = std::make_unique<CheckPoint>(Vector3(-90.0f, 125.0f, 62.0f));
	//プレイヤー-116.0f, 5.0f, 134.0f

	m_builModel[0] = Model::CreateFromCMO(device, L"Resources/Models/Building1.cmo", *GameContext().Get<EffectFactory>());
	m_builModel[1] = Model::CreateFromCMO(device, L"Resources/Models/Building2.cmo", *GameContext().Get<EffectFactory>());
	m_builModel[2] = Model::CreateFromCMO(device, L"Resources/Models/Building3.cmo", *GameContext().Get<EffectFactory>());
	//高い
	Vector3 tallSize = Vector3(12.0f, 19.8f, 13.7f);
	const int buil1Num = 3;

	std::unique_ptr<Building> buil1[buil1Num];
	
	buil1[0] = std::make_unique<Building>(Vector3(40.0f, 12.0f, 0.0f), tallSize);
	buil1[1] = std::make_unique<Building>(Vector3(-105.0f, 12.0f, 108.0), tallSize);
	buil1[2] = std::make_unique<Building>(Vector3(-70.0f, 12.0f, 81.0), tallSize);


	//足場
	Vector3 footingSize = Vector3(11.8f, 1.0f, 7.9f);
	const int buil2Num = 2;

	std::unique_ptr<Building> buil2[buil2Num];
	
	buil2[0] = std::make_unique<Building>(Vector3(-90.0f, 120.0f, 60.0f), footingSize);
	buil2[1] = std::make_unique<Building>(Vector3(-70.0f,  90.0f, 40.0f), footingSize);
	
	//小さい
	Vector3 shortSize = Vector3(7.45f, 7.35f, 7.6f);
	const int buil3Num = 1;
	
	std::unique_ptr<Building> buil3[buil3Num];

	buil3[0] = std::make_unique<Building>(Vector3(-116.0f, 7.0f, 120.0), shortSize);






	for (int i = 0; i < buil1Num; i++)
	{
		buil1[i]->SetModel(m_builModel[0].get());
	}
	for (int i = 0; i < buil2Num; i++)
	{
		buil2[i]->SetModel(m_builModel[1].get());
	}
	for (int i = 0; i < buil3Num; i++)
	{
		buil3[i]->SetModel(m_builModel[2].get());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//スカイドーム
	std::unique_ptr<SkyDome> skyDome = std::make_unique<SkyDome>();

	m_gameObjectManager->Add(std::move(skyDome));
	//ゲームオブジェクトに追加
	for (int i = 0; i < 1; i++)
	{
		m_gameObjectManager->Add(std::move(ground[i]));
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_gameObjectManager->Add(std::move(checkPoint));
	for (int i = 0; i < buil1Num; i++)
	{
		m_gameObjectManager->Add(std::move(buil1[i]));
	}
	for (int i = 0; i < buil2Num; i++)
	{
		m_gameObjectManager->Add(std::move(buil2[i]));
	}
	for (int i = 0; i < buil3Num; i++)
	{
		m_gameObjectManager->Add(std::move(buil3[i]));
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_gameObjectManager->Add(std::move(tpsCamera));
	m_gameObjectManager->Add(std::move(player));
	

	m_collisionManager->AllowCollision("Player", "Ground");
}

/// <summary>
/// アップデート
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void PlayState::Update(float elapsedTime)
{
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();

	//ポーズ画面
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::P))
	{
		using stateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PushState(stateID::PAUSE_STATE);
	}

	m_collisionManager->DetectCollision();
	//ゲームオブジェクトアップデート
	m_gameObjectManager->Update(elapsedTime);

	m_effectManager->SetRenderState(tpsCamera->GetPosition() + tpsCamera->GetEyePosition(), tpsCamera->GetViewMatrix(), GameContext().Get<Projection>()->GetMatrix());
	m_effectManager->Update(*GameContext().Get<DX::StepTimer>());
}

void PlayState::Render()
{
	//ゲームオブジェクト描画
	m_gameObjectManager->Render();
	
	//デバック表記
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PlayState");
	debugFont->draw();
	debugFont->print(10, 40, L"[P] Pause");
	debugFont->draw();

	m_effectManager->Render();
}

void PlayState::Finalize()
{

}
