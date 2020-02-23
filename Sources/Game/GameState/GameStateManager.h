//======================================================
// File Name		: GameStateManager.h
// Summary		: ゲームステイトマネジャー
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
	//ステイトID
	enum GameStateID
	{
		NONE_STATE = -1,
		TITLE_STATE,
		PLAY_STATE,
		PAUSE_STATE,
		RESULT_STATE,
	};

private:
	//名前変更
	using IGameStatePtr         = std::unique_ptr<IGameState>;
	using IGameStateStack       = std::deque<IGameStatePtr>;
	using IGameStateFactory     = std::function<IGameStatePtr()>;
	using IGameStateFactoryList = std::unordered_map<GameStateID, IGameStateFactory>;


public://コンストラクタ　デストラクタ
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

private://メンバー変数
	IGameStateFactoryList m_stateFactories;
	IGameStateStack       m_states;
	int                   m_popCount;
	GameStateID           m_nextStateName;
};


template<typename State>
/// <summary>
/// ステイト生成
/// </summary>
/// <returns></returns>
 GameStateManager::IGameStatePtr GameStateManager::CrateState()
{
	return std::make_unique<State>();
}



template<typename State>
/// <summary>
/// ゲームステイトを登録
/// </summary>
/// <param name="id">ステイトID</param>
 void GameStateManager::RegisterState(const GameStateID id)
{
	 m_stateFactories.emplace(std::make_pair(id, CrateState<State>));
}
