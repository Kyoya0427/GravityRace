//======================================================
// File Name	: GameObject.cpp
// Summary	: ゲームオブジェクトインターフェイス
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "GameObject.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="tag"></param>
GameObject::GameObject(ObjectID tag)
	: m_tag(tag)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_rotation()
	, m_size(1.0f,1.0f,1.0f)
{
}

/// <summary>
/// デストラク
/// </summary>
GameObject::~GameObject()
{
}

/// <summary>
/// 無効に変換
/// </summary>
void GameObject::Invalidate()
{
	m_isValid = false;
}

/// <summary>
/// オブジェクト消去
/// </summary>
/// <param name="object"></param>
void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}
