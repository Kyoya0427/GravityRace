//======================================================
// File Name	: SkyDome.cpp
// Summary	: �X�J�C�h�[��
// Author		: Kyoya Sakamoto
//======================================================

#include "SkyDome.h"

#include <Effects.h>

#include <Utils\GameContext.h>
#include <Framework\DeviceResources.h>
#include <Utils\Projection.h>

#include <Game\Object\GameObject.h>

#include <Game\Camera\TPSCamera.h>


using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
SkyDome::SkyDome()
{
	ID3D11Device*          device = GameContext().Get<DX::DeviceResources>()->GetD3DDevice();

	m_position = Vector3::Zero;

	m_model = Model::CreateFromCMO(device, L"Resources/Models/Skydome.cmo", *GameContext().Get<EffectFactory>());
	m_model->UpdateEffects([](DirectX::IEffect* effect) {
		DirectX::IEffectLights* lights = dynamic_cast<DirectX::IEffectLights*>(effect);
		if (lights) {
			// ���C�g�̉e�����Ȃ��� 
			lights->SetAmbientLightColor(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
		if (basicEffect) {
			// �G�~�b�V�����F�𔒂ɐݒ肷�� 
			basicEffect->SetEmissiveColor(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
		}
	});
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SkyDome::~SkyDome()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void SkyDome::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// �`��
/// </summary>
void SkyDome::Render(const DX::StepTimer& timer)
{
	timer;
	DX::DeviceResources* deviceResources = GameContext().Get<DX::DeviceResources>();
	ID3D11DeviceContext*   deviceContext = deviceResources->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext().Get<DirectX::CommonStates>();
	Projection*  projection = GameContext().Get<Projection>();
	TPSCamera* tpsCamera = GameContext().Get<TPSCamera>();

	m_position = Vector3::Zero;

	m_world = DirectX::SimpleMath::Matrix::Identity;
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_model->Draw(deviceContext, *state, m_world, tpsCamera->GetViewMatrix(), projection->GetMatrix());

}



void SkyDome::HitContact(GameObject * object, RaycastHit * raycastHit)
{
	object;
	raycastHit;
}
