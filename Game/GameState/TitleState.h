//======================================================
// File Name	 : TitleState.h
// Summary	 : �^�C�g���X�e�C�g
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

#include "IGameState.h"

class TitleState :public IGameState
{
public:
	TitleState();

public:
	virtual ~TitleState();

public:
	void Initialize() override;
	void Update(float elapsedTime)     override;
	void Render()     override;
	void Finalize()   override;

private:
	float m_count;
};

