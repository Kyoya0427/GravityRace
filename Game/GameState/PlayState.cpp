//======================================================
// File Name	 : play.cpp
// Summary	 : �v���C�X�e�C�g
// Author		 : Kyoya Sakamoto
//======================================================
//#include <pch.h>

#include "PlayState.h"
#include "GameStateManager.h"

#include <Keyboard.h>
#include <Effects.h>

#include <Source\DebugFont.h>

#include <Common\DeviceResources.h>
#include <Common\GameContext.h>
#include <Common\Projection.h>
#include <Common\StepTimer.h>

#include <Object\GameObjectManager.h>

#include <Collider\CollisionManager.h>

#include <Source\GridFloor.h>

#include <Camera\TPSCamera.h>

#include <Player\Player.h>

#include <Stage\Ground.h>
#include <Stage\SkyDome.h>
#include <Stage\CheckPoint.h>
#include <Stage\Building.h>

#include <Effect\EnergyEffectManager.h>
#include <Effect\ConcentrationLineEffectManager.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayState::PlayState()
	:IGameState()
	, m_effectManager(nullptr)
	, m_concentrationLineEffectManager(nullptr)
	,m_count(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayState::~PlayState()
{
	if (m_effectManager != nullptr) {
		m_effectManager->Lost();
		delete m_effectManager;
		m_effectManager = nullptr;
	}
	if (m_concentrationLineEffectManager != nullptr) {
		m_concentrationLineEffectManager->Lost();
		delete m_concentrationLineEffectManager;
		m_concentrationLineEffectManager = nullptr;
	}
}

/// <summary>
/// �C�j�V�����C�Y
/// </summary>
void PlayState::Initialize()
{
	//�Q�[���R���e�L�X�g
	ID3D11Device* device = GameContext().Get<DX::DeviceResources>()->GetD3DDevice();

	//�Q�[���I�u�W�F�N�g�}�l�W���[
	m_gameObjectManager = std::make_unique<GameObjectManager>();
	GameContext().Register<GameObjectManager>(m_gameObjectManager.get());

	//�R���W�����}�l�[�W���[
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext().Register<CollisionManager>(m_collisionManager.get());

	//�G�t�F�N�g�t�@�N�g���[�ݒ�
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(device);
	factory->SetDirectory(L"Resources/Models");
	GameContext().Register<EffectFactory>(factory);

	//�J�����쐬
	std::unique_ptr<TPSCamera> tpsCamera = std::make_unique<TPSCamera>();
	GameContext().Register<TPSCamera>(tpsCamera.get());
	
	//�v���C���[�쐬
	std::unique_ptr<Player> player = std::make_unique<Player>();
	GameContext().Register<Player>(player.get());

	////�n�ʍ쐬
	std::unique_ptr<Ground> ground[1];
	ground[0] = std::make_unique<Ground>(Vector3(  0.0f, 0.0f,   0.0f));

	m_effectManager = new EnergyEffectManager();
	m_effectManager->Create(GameContext().Get<DX::DeviceResources>(), L"Resources\\Textures\\energy.png", 1);
	m_effectManager->InitializeCorn(5, Vector3(0, 0, 0), Vector3(0, 1, 0));
	m_effectManager->SetRenderState(tpsCamera->GetPosition() + tpsCamera->GetEyePosition(), tpsCamera->GetViewMatrix() , GameContext().Get<Projection>()->GetMatrix());

	m_concentrationLineEffectManager = new ConcentrationLineEffectManager();
	m_concentrationLineEffectManager->Create(GameContext().Get<DX::DeviceResources>(), L"Resources\\Textures\\concentrationLine.png", 1);
	m_concentrationLineEffectManager->InitializeCorn(5, Vector3(0, 0, 0), Vector3(0, 1, 0));
	m_concentrationLineEffectManager->SetRenderState(tpsCamera->GetPosition() + tpsCamera->GetEyePosition(), tpsCamera->GetViewMatrix(), GameContext().Get<Projection>()->GetMatrix());

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//stage
	std::unique_ptr<CheckPoint> checkPoint = std::make_unique<CheckPoint>(Vector3(-90.0f, 125.0f, 62.0f));
	//�v���C���[-116.0f, 5.0f, 134.0f

	m_builModel[0] = Model::CreateFromCMO(device, L"Resources/Models/Building1.cmo", *GameContext().Get<EffectFactory>());
	m_builModel[1] = Model::CreateFromCMO(device, L"Resources/Models/Building2.cmo", *GameContext().Get<EffectFactory>());
	m_builModel[2] = Model::CreateFromCMO(device, L"Resources/Models/Building3.cmo", *GameContext().Get<EffectFactory>());
	//����
	Vector3 tallSize = Vector3(12.0f, 19.8f, 13.7f);
	const int buil1Num = 4;
	
	std::unique_ptr<Building> buil1[buil1Num];
	
	buil1[0] = std::make_unique<Building>(Vector3(40.0f, 12.0f, 0.0f), tallSize);
	buil1[1] = std::make_unique<Building>(Vector3(-105.0f, 12.0f, 108.0), tallSize);
	buil1[2] = std::make_unique<Building>(Vector3(-70.0f, 12.0f, 81.0), tallSize);
	buil1[3] = std::make_unique<Building>(Vector3(-70.0f, 12.0f, 60.0), tallSize);


	//����
	Vector3 footingSize = Vector3(11.8f, 1.0f, 7.9f);
	const int buil2Num = 3;

	std::unique_ptr<Building> buil2[buil2Num];
	
	buil2[0] = std::make_unique<Building>(Vector3(-90.0f, 120.0f, 60.0f), footingSize);
	buil2[1] = std::make_unique<Building>(Vector3(-70.0f,  90.0f, 40.0f), footingSize);
	buil2[2] = std::make_unique<Building>(Vector3(-45.0f,  10.0f, 10.0f), footingSize);
	
	//������
	Vector3 shortSize = Vector3(7.45f, 7.35f, 7.6f);
	const int buil3Num = 2;
	
	std::unique_ptr<Building> buil3[buil3Num];

	buil3[0] = std::make_unique<Building>(Vector3(-116.0f, 7.0f, 120.0), shortSize);
	buil3[1] = std::make_unique<Building>(Vector3(-90.0f, 7.0f, 100.0), shortSize);






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


	//�X�J�C�h�[��
	std::unique_ptr<SkyDome> skyDome = std::make_unique<SkyDome>();

	m_gameObjectManager->Add(std::move(skyDome));
	//�Q�[���I�u�W�F�N�g�ɒǉ�
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
/// �A�b�v�f�[�g
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void PlayState::Update(float elapsedTime)
{
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();

	//�|�[�Y���
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::P))
	{
		using stateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PushState(stateID::PAUSE_STATE);
	}

	m_collisionManager->DetectCollision();
	//�Q�[���I�u�W�F�N�g�A�b�v�f�[�g
	m_gameObjectManager->Update(elapsedTime);

	m_effectManager->SetRenderState(tpsCamera->GetPosition() + tpsCamera->GetEyePosition(), tpsCamera->GetViewMatrix(), GameContext().Get<Projection>()->GetMatrix());
	m_effectManager->Update(*GameContext().Get<DX::StepTimer>());

	m_concentrationLineEffectManager->SetRenderState(tpsCamera->GetPosition() + tpsCamera->GetEyePosition(), tpsCamera->GetViewMatrix(), GameContext().Get<Projection>()->GetMatrix());
	m_concentrationLineEffectManager->Update(*GameContext().Get<DX::StepTimer>());
}

void PlayState::Render()
{
	//�Q�[���I�u�W�F�N�g�`��
	m_gameObjectManager->Render();
	
	//�f�o�b�N�\�L
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PlayState");
	debugFont->draw();
	debugFont->print(10, 40, L"[P] Pause");
	debugFont->draw();

	m_effectManager->Render();
	m_concentrationLineEffectManager->Render();
}

void PlayState::Finalize()
{

}
