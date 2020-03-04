//======================================================
// File Name	 : PlayState.h
// Summary	 : プレイステイト
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <memory>

#include <Model.h>

#include "IGameState.h"


class GameObjectManager;
class CollisionManager;
class StageManager;

class PlayState :public IGameState
{
public:
	PlayState();

public:
	virtual ~PlayState();

public:
	//初期化
	void Initialize() override;
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render(const DX::StepTimer& timer) override;
	//終了
	void Finalize() override;

private:

	std::unique_ptr<GameObjectManager>  m_gameObjectManager;
	std::unique_ptr<CollisionManager>   m_collisionManager;
	std::unique_ptr<StageManager>       m_stageManager;
};

