//======================================================
// File Name	: ResultState.h
// Summary	: リザルトステイト
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include "IGameState.h"

class ResultState :public IGameState
{
public:
	ResultState();

public:
	virtual ~ResultState();

public:
	void Initialize() override;
	void Update(float elapsedTime)     override;
	void Render()     override;
	void Finalize()   override;

private:
	float m_count;
};

