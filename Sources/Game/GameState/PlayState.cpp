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


using namespace DirectX;
using namespace DirectX::SimpleMath;


/// <summary>
/// �R���X�g���N�^
/// </summary>
PlayState::PlayState()
	:IGameState()
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

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void PlayState::Update(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// �`��
/// </summary>
/// <param name="timer"></param>
void PlayState::Render(const DX::StepTimer& timer)
{
	timer;
}

/// <summary>
/// �I��
/// </summary>
void PlayState::Finalize()
{

}
