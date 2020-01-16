#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{

	float2 uv = input.Tex;

	float2 vec = uv - float2(0.1f, 0.1f);

	float angle = atan2(vec.y, vec.x);

	angle -= 3.14f / 2;
	if (angle < -3.14f) {
		angle += 6.28f;
	}

	float4 energy = Energy;

	float4 base = tex.Sample(samLinear, input.Tex);

	if ((angle+3.14f)/6.28f > energy.x)
	{
		base.a = 0;
	}


	if (length(vec) < 0.05f) 
	{
		base.a = 0;
	}

	if (length(vec) > 0.07f) 
	{
		base.a = 0;
	}

	return base;
}