#pragma once

#include <Framework\Game.h>

class MyGame 
{
 public:
	 //�R���X�g���N�^
	 MyGame();
	 ~MyGame();

	 void Initialize();
	 void Update(const DX::StepTimer& timer);
	 void Render(const DX::StepTimer& timer);
	 void Finalize();
};