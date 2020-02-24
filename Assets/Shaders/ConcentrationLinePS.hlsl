#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float random(float2 uv)
{
	//いい感じのランダムな数字（0～1)を返す
	//引数uvはUV(input.Texなど）を渡さないとランダムな値にならない
	return frac(sin(dot(uv, float2(12.9898f, 78.233f)))* 43758.5453f);
}

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 diff = tex.Sample(samLinear, input.Tex);
	float2 uv = input.Tex;

	float PI = 3.14159265359f;

	float angle = atan2(uv.y - 0.7f, uv.x - 0.5f);
	angle += PI;
	angle /= PI * 2;

	float d = distance(uv, float2(0.5f, 0.7f));

	float speed = floor(Time.x * 100) / 100.0f;

	float4 l = ConcentrationLine;

	if (l.x == 1 && l.y == 1)
	{
		if (random(floor(angle * 100) + speed) < 0.1f)
		{
			diff.a = 1;
		}
		else {
			diff.a = 0;
		}
		if (d < 0.4f) {
			if (d < 0.2f) {
				diff.a = 0;
			}
			else {
				diff.a *= (d - 0.2f) / 0.2f;
			}
		}
	}
	else
	{
		diff.a = 0;
	}
	return diff;
}
