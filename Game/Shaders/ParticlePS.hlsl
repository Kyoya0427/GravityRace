#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{

	float2 uv = input.Tex;

	float2 vec = uv - float2(0.5f, 0.5f);

	float angle = atan2(vec.y, vec.x);

	float4 base = tex.Sample(samLinear, input.Tex);

	if (angle > Time.z*3.14f) {
		base.a = 0;
	}

	return base;
}