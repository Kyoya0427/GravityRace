//======================================================
// File Name	: PlayState.h
// Summary	: �v���C�X�e�C�g
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
/// �R���X�g���N�^
/// </summary>
PlayState::PlayState()
	: IGameState()
	, m_gameObjectManager()
	, m_collisionManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayState::~PlayState()
{

}

/// <summary>
/// ������
/// </summary>
void PlayState::Initialize()
{
	//�f�o�C�X�擾
	ID3D11Device* device = GameContext().Get<DX::DeviceResources>()->GetD3DDevice();

	//�Q�[���I�u�W�F�N�g�}�l�W���[����
	m_gameObjectManager = std::make_unique<GameObjectManager>();
	GameContext().Register<GameObjectManager>(m_gameObjectManager.get());

	//�R���C�_�[�}�l�W���[����
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext().Register<CollisionManager>(m_collisionManager.get());

	//���f���t�@�C����w��
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	factory->SetDirectory(L"Resources/Models");
	GameContext().Register<EffectFactory>(factory);

	//TPS�J��������
	std::unique_ptr<TPSCamera> tpsCamera = std::make_unique<TPSCamera>();
	GameContext().Register<TPSCamera>(tpsCamera.get());

	//�v���C���[����
	std::unique_ptr<Player> player = std::make_unique<Player>();
	GameContext().Register<Player>(player.get());

	//�I�u�W�F�N�g�}�l�W���[�ɒǉ�
	m_gameObjectManager->Add(std::move(tpsCamera));
	m_gameObjectManager->Add(std::move(player));

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void PlayState::Update(const DX::StepTimer& timer)
{
	timer;
	//�|�[�Y���
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::P))
	{
		using stateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PushState(stateID::PAUSE_STATE);
	}

	//�I�u�W�F�N�g�}�l�W���[�X�V
	m_gameObjectManager->Update(timer);

}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer"></param>
void PlayState::Render(const DX::StepTimer& timer)
{
	//�I�u�W�F�N�g�}�l�W���[�`��
	m_gameObjectManager->Render(timer);
}

/// <summary>
/// �I��
/// </summary>
void PlayState::Finalize()
{

}
