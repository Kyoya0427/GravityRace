//======================================================
// File Name	 : PauseState.cpp
// Summary	 : �|�[�Y�X�e�C�g
// Author		 : Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "PauseState.h"
#include "GameStateManager.h"

#include <Keyboard.h>

#include <Utils\GameContext.h>


/// <summary>
/// �R���X�g���N�^
/// </summary>
PauseState::PauseState()
	:IGameState()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PauseState::~PauseState()
{
}
/// <summary>
/// �C�j�V�����C�Y
/// </summary>
void PauseState::Initialize()
{
}
/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void PauseState::Update(const DX::StepTimer& timer)
{
	timer;
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	if (keyState.IsKeyDown(DirectX::Keyboard::Z))
	{
		using StateID = GameStateManager::GameStateID;
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
	}

	if (keyState.IsKeyDown(DirectX::Keyboard::X))
	{
		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->PopState();
	}
}
/// <summary>
/// �����_�[
/// </summary>
void PauseState::Render(const DX::StepTimer& timer)
{
}
/// <summary>
/// �t�@�C�i���C�Y
/// </summary>
void PauseState::Finalize()
{
}
