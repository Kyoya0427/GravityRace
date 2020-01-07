#pragma once

#include <SimpleMath.h>

struct BoxShape
{
	BoxShape():pos(),ext(){}

	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Vector3 ext;
};