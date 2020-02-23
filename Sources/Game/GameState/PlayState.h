//======================================================
// File Name	 : play.h
// Summary	 : プレイステイト
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <memory>

#include <Model.h>

#include "IGameState.h"



class GridFloor;
class GameObjectManager;
class CollisionManager;
class EnergyEffectManager;
class ConcentrationLineEffectManager;

class PlayState :public IGameState
{
public:
	PlayState();

public:
	virtual ~PlayState();

public:
	void Initialize() override;
	void Update(float elapsedTime)     override;
	void Render()     override;
	void Finalize()   override;

private:
	
	std::unique_ptr<DirectX::Model>     m_builModel[3];

	std::unique_ptr<GameObjectManager>  m_gameObjectManager;
	std::unique_ptr<CollisionManager>   m_collisionManager;

	EnergyEffectManager*                m_effectManager;
	ConcentrationLineEffectManager *    m_concentrationLineEffectManager;
};

