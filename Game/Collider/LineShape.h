//======================================================
// File Name	: LineShape.h
// Summary	: ���C��
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <SimpleMath.h>

struct LineShape
{
	LineShape():posA(0.0f,0.0f,0.0f),posB(0.0f, 0.0f, 0.0f){}
	DirectX::SimpleMath::Vector3 posA;
	DirectX::SimpleMath::Vector3 posB;
};