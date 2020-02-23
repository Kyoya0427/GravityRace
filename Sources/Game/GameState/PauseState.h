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
	void Update(float elapsedTime) override;
	void Render() override;
	void Finalize() override;
};

