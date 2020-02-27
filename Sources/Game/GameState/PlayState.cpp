//======================================================
// File Name	: PlayState.h
// Summary	: プレイステイト
// Author		: Kyoya Sakamoto
//======================================================
#include "PlayState.h"
#include "GameStateManager.h"

#include <Keyboard.h>
#include <Effects.h>
#include <SimpleMath.h>

#include <Game\Collider\CollisionManager.h>
#include <Game\Object\GameObjectManager.h>
#include <Game\Camera\TPSCamera.h>
#include <Game\Player\Player.h>
#include <Game\Stage\Ground.h>


#include <Utils\GameContext.h>

#include <Framework\DeviceResources.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// コンストラクタ
/// </summary>
PlayState::PlayState()
	: IGameState()
	, m_gameObjectManager()
	, m_collisionManager()
{
}

/// <summary>
/// デストラクタ
/// </summary>
PlayState::~PlayState()
{

}

/// <summary>
/// 初期化
/// </summary>
void PlayState::Initialize()
{
	//デバイス取得
	ID3D11Device* device = GameContext().Get<DX::DeviceResources>()->GetD3DDevice();

	//ゲームオブジェクトマネジャー生成
	m_gameObjectManager = std::make_unique<GameObjectManager>();
	GameContext().Register<GameObjectManager>(m_gameObjectManager.get());

	//コライダーマネジャー生成
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext().Register<CollisionManager>(m_collisionManager.get());

	//モデルファイル先指定
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	factory->SetDirectory(L"Resources/Models");
	GameContext().Register<EffectFactory>(factory);

	//TPSカメラ生成
	std::unique_ptr<TPSCamera> tpsCamera = std::make_unique<TPSCamera>();
	GameContext().Register<TPSCamera>(tpsCamera.get());

	//プレイヤー生成
	std::unique_ptr<Player> player = std::make_unique<Player>();
	GameContext().Register<Player>(player.get());

	//オブジェクトマネジャーに追加
	m_gameObjectManager->Add(std::move(tpsCamera));
	m_gameObjectManager->Add(std::move(player));

}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void PlayState::Update(const DX::StepTimer& timer)
{
	timer;
	//ポーズ画面
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::P))
	{
		using stateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PushState(stateID::PAUSE_STATE);
	}

	//オブジェクトマネジャー更新
	m_gameObjectManager->Update(timer);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="timer"></param>
void PlayState::Render(const DX::StepTimer& timer)
{
	//オブジェクトマネジャー描画
	m_gameObjectManager->Render(timer);
}

/// <summary>
/// 終了
/// </summary>
void PlayState::Finalize()
{

}
