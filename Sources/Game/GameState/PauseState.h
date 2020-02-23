//======================================================
// File Name	 : PauseState.h
// Summary	 : ポーズステイト
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include "IGameState.h"

class PauseState :public IGameState
{
public:
	PauseState();

public:
	virtual ~PauseState();

public:
	void Initialize() override;
	void Update(const DX::StepTimer& timer) override;
	void Render(const DX::StepTimer& timer) override;
	void Finalize() override;
};

