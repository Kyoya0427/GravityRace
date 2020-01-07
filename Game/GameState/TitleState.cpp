//======================================================
// File Name	: TitleState.cpp
// Summary	: �^�C�g���X�e�C�g
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "TitleState.h"

#include <Game\Source\DebugFont.h>

#include <Game\Common\GameContext.h>

#include "GameStateManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TitleState::TitleState()
	:IGameState()
	, m_count(0)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TitleState::~TitleState()
{
}

/// <summary>
/// �C�j�V�����C�Y
/// </summary>
void TitleState::Initialize()
{
	m_count = 0.0f;
}

/// <summary>
///�A�b�v�f�[�g 
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void TitleState::Update(float elapsedTime)
{
	
	m_count += elapsedTime;

	if (m_count > 3)
	{
		using StateID = GameStateManager::GameStateID;

		GameStateManager* gameStateManager = GameContext().Get<GameStateManager>();
		gameStateManager->RequestState(StateID::PLAY_STATE);
		m_count = 0.0;
	}

}

/// <summary>
/// �`��
/// </summary>
void TitleState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"TitleState");
	debugFont->draw();
	debugFont->print(10, 40, L"%.2f / 3",m_count);
	debugFont->draw();
}

/// <summary>
/// �t�@�C�i���C�Y
/// </summary>
void TitleState::Finalize()
{
}
