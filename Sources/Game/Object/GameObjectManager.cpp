//======================================================
// File Name	: GameObjectManager.cpp
// Summary	: ゲームオブジェクトマネジャー
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "GameObjectManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
GameObjectManager::GameObjectManager()
	: m_objects()
	, m_objectQueue()
{
}

/// <summary>
/// デストラクタ
/// </summary>
GameObjectManager::~GameObjectManager()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void GameObjectManager::Update(const DX::StepTimer& timer)
{
	DestroyObjects();


	if (!m_objectQueue.empty())
	{
		AcceptObjects();
	}


	UpdateObjects(timer);
}

/// <summary>
/// 描画
/// </summary>
void GameObjectManager::Render(const DX::StepTimer& timer)
{
	for (GameObjectPtr& object : m_objects)
	{
		object->Render(timer);
	}
}

/// <summary>
/// オブジェクト追加処理
/// </summary>
/// <param name="object"></param>
void GameObjectManager::Add(GameObjectPtr&& object)
{
	m_objectQueue.push_back(std::move(object));
}

/// <summary>
/// 追加したオブジェクト名を取得
/// </summary>
/// <param name="tag">オブジェクト名</param>
/// <returns>オブジェクト</returns>
std::vector<GameObject*> GameObjectManager::Find(GameObject::ObjectID tag) const
{
	std::vector<GameObject*> result;

	for (const GameObjectPtr& object : m_objects)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	for (const GameObjectPtr& object : m_objectQueue)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	return result;
}


/// <summary>
/// 追加したオブジェクト名を取得
/// </summary>
/// <param name="tag">オブジェクト</param>
/// <returns>オブジェクト</returns>
std::vector<GameObject*> GameObjectManager::Find(std::function<bool(GameObject*)> predicate) const
{
	std::vector<GameObject*> result;

	for (const GameObjectPtr& object : m_objects)
	{
		if (predicate(object.get()))
		{
			result.push_back(object.get());
		}
	}

	for (const GameObjectPtr& object : m_objectQueue)
	{
		if (predicate(object.get()))
		{
			result.push_back(object.get());
		}
	}

	return result;
}

/// <summary>
/// 追加オブジェクトの更新
/// </summary>
/// <param name="elapsedTime">タイマー</param>
void GameObjectManager::UpdateObjects(const DX::StepTimer& timer)
{
	// 実装1 範囲for文
	for (GameObjectPtr& object : m_objects)
	{
		object->Update(timer);
	}
}

/// <summary>
/// 更新されるベクターに追加
/// </summary>
void GameObjectManager::AcceptObjects()
{
	// 要素の移動
	m_objects.splice(m_objects.end(), m_objectQueue);
}

/// <summary>
/// 追加したオブジェクトを消去
/// </summary>
void GameObjectManager::DestroyObjects()
{
	// 実装2 条件一致する全ての要素を削除
	m_objects.remove_if(std::mem_fn(&GameObject::IsInvalid));
}
