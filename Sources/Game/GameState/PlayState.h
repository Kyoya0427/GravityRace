//======================================================
// File Name	 : play.h
// Summary	 : プレイステイト
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include <memory>

#include <Model.h>

#include "IGameState.h"





class PlayState :public IGameState
{
public:
	PlayState();

public:
	virtual ~PlayState();

public:
	void Initialize() override;
	void Update(const DX::StepTimer& timer)     override;
	void Render(const DX::StepTimer& timer)     override;
	void Finalize()   override;

private:
	
	
};

