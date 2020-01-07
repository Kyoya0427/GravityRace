//======================================================
// File Name		: GameStateManager.h
// Summary		: �Q�[���X�e�C�g�}�l�W���[
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <functional>
#include <memory>
#include <deque>
#include <unordered_map>

class IGameState;

class GameStateManager
{
public:
	//�X�e�C�gID
	enum GameStateID
	{
		NONE_STATE = -1,
		TITLE_STATE,
		PLAY_STATE,
		PAUSE_STATE,
		RESULT_STATE,
	};

private:
	//���O�ύX
	using IGameStatePtr         = std::unique_ptr<IGameState>;
	using IGameStateStack       = std::deque<IGameStatePtr>;
	using IGameStateFactory     = std::function<IGameStatePtr()>;
	using IGameStateFactoryList = std::unordered_map<GameStateID, IGameStateFactory>;


public://�R���X�g���N�^�@�f�X�g���N�^
	GameStateManager();
	~GameStateManager();

private:
	template<typename State>
	static IGameStatePtr CrateState();

public:
	
	void Update(float elapsedTime);
	void Render();

public:
	template<typename State>
	void RegisterState(const GameStateID id);
	
	void SetStartState(const GameStateID id);

	void RequestState(const GameStateID id);
	void PushState(const GameStateID id);
	void PopState(int count = 1);

	

private:
	void ChangeState();

private://�����o�[�ϐ�
	IGameStateFactoryList m_stateFactories;
	IGameStateStack       m_states;
	int                   m_popCount;
	GameStateID           m_nextStateName;
};


template<typename State>
/// <summary>
/// �X�e�C�g����
/// </summary>
/// <returns></returns>
 GameStateManager::IGameStatePtr GameStateManager::CrateState()
{
	return std::make_unique<State>();
}



template<typename State>
/// <summary>
/// �Q�[���X�e�C�g��o�^
/// </summary>
/// <param name="id">�X�e�C�gID</param>
 void GameStateManager::RegisterState(const GameStateID id)
{
	 m_stateFactories.emplace(std::make_pair(id, CrateState<State>));
}