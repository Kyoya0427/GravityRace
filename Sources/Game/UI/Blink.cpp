//======================================================
// File Name	: Blink.cpp
// Summary	: �_�ŃN���X
// Author		: Kyoya Sakamoto
//======================================================
#include "pch.h"
#include "Blink.h"

Blink::Blink()
	: m_blinkFlag(true), m_blinkTime(0.0f), m_interval(0.0f), m_stopFlag(true)
{
}

void Blink::Initialize(float interval)
{
	m_interval = interval;
}

void Blink::Update(float elapsedTime)
{
	if (m_stopFlag) return;

	m_blinkTime += elapsedTime;
	if (m_blinkTime >= m_interval)
	{
		m_blinkFlag = !m_blinkFlag;
		m_blinkTime = 0.0f;
	}

}

bool Blink::GetState()
{
	return m_blinkFlag;
}

void Blink::Reset(bool flag)
{
	m_blinkFlag = flag;
	m_blinkTime = 0.0f;
}

void Blink::Start()
{
	m_stopFlag = false;
}

void Blink::Stop()
{
	m_stopFlag = true;
}
