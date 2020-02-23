//======================================================
// File Name	: MyGame.cpp
// Summary	: マイゲーム
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SimpleMath.h>


#include <Framework\Game.h>
#include <Utils\Projection.h>

class MyGame 
{
 public:
	 //コンストラクタ
	 MyGame();
	 ~MyGame();

	 void Initialize();
	 void Update(const DX::StepTimer& timer);
	 void Render(const DX::StepTimer& timer);
	 void Finalize();

 private:


 private:
	 
	 
	

};