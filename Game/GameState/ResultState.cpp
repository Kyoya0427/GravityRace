//======================================================
// File Name	: ResultState.cpp
// Summary	: ���U���g�X�e�C�g
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "ResultState.h"

#include <Game\Source\DebugFont.h>

#include <Game\Common\GameContext.h>

#include "GameStateManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultState::ResultState()
	:IGameState()
	, m_count(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultState::~ResultState()
{
}

/// <summary>
/// �C�j�V�����C�Y
/// </summary>
void ResultState::Initialize()
{
	m_count = 0.0f;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void ResultState::Update(float elapsedTime)
{
	
	m_count += elapsedTime;

	if (m_count > 3)
	{
		using StateID = GameStateManager::GameStateID;

		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::TITLE_STATE);
		m_count = 0.0f;
	}
}

/// <summary>
///�`��
/// </summary>
void ResultState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"ResultState");
	debugFont->draw();
	debugFont->print(10, 40, L"%.2f / 3", m_count);
	debugFont->draw();
}

/// <summary>
/// �t�@�C�i���C�Y
/// </summary>
void ResultState::Finalize()
{
}
