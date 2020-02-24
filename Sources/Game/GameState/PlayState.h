//======================================================
// File Name	 : PlayState.h
// Summary	 : �v���C�X�e�C�g
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
	//������
	void Initialize() override;
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render(const DX::StepTimer& timer) override;
	//�I��
	void Finalize() override;

private:
	
	
};

