//======================================================
// File Name	 : IGameState.h
// Summary	 : ゲームステイトのインターフェイス
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once
#include <Framework\StepTimer.h>

class IGameState
{
public:
	IGameState() = default;

public:
	virtual ~IGameState() = default;

public:
	virtual void Initialize()  = 0;
	virtual void Update(const DX::StepTimer& timer)      = 0;
	virtual void Render(const DX::StepTimer& timer)      = 0;
	virtual void Finalize()    = 0;
};