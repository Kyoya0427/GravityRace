//======================================================
// File Name	 : PlayState.h
// Summary	 : �v���C�X�e�C�g
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
	//������
	void Initialize() override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render(const DX::StepTimer& timer) override;
	//�I��
	void Finalize() override;

private:

	std::unique_ptr<GameObjectManager>  m_gameObjectManager;
	std::unique_ptr<CollisionManager>   m_collisionManager;
	std::unique_ptr<StageManager>       m_stageManager;
};

