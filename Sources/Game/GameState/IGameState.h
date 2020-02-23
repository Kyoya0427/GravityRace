//======================================================
// File Name	 : IGameState.h
// Summary	 : �Q�[���X�e�C�g�̃C���^�[�t�F�C�X
// Author		 : Kyoya Sakamoto
//======================================================
#pragma once

class IGameState
{
public:
	IGameState() = default;

public:
	virtual ~IGameState() = default;

public:
	virtual void Initialize()  = 0;
	virtual void Update(float elapsedTime)      = 0;
	virtual void Render()      = 0;
	virtual void Finalize()    = 0;
};