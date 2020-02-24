//======================================================
// File Name	: GameObjectManager.cpp
// Summary	: �Q�[���I�u�W�F�N�g�}�l�W���[
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "GameObjectManager.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
GameObjectManager::GameObjectManager()
	: m_objects()
	, m_objectQueue()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObjectManager::~GameObjectManager()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
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
/// �`��
/// </summary>
void GameObjectManager::Render(const DX::StepTimer& timer)
{
	for (GameObjectPtr& object : m_objects)
	{
		object->Render(timer);
	}
}

/// <summary>
/// �I�u�W�F�N�g�ǉ�����
/// </summary>
/// <param name="object"></param>
void GameObjectManager::Add(GameObjectPtr&& object)
{
	m_objectQueue.push_back(std::move(object));
}

/// <summary>
/// �ǉ������I�u�W�F�N�g�����擾
/// </summary>
/// <param name="tag">�I�u�W�F�N�g��</param>
/// <returns>�I�u�W�F�N�g</returns>
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
/// �ǉ������I�u�W�F�N�g�����擾
/// </summary>
/// <param name="tag">�I�u�W�F�N�g</param>
/// <returns>�I�u�W�F�N�g</returns>
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
/// �ǉ��I�u�W�F�N�g�̍X�V
/// </summary>
/// <param name="elapsedTime">�^�C�}�[</param>
void GameObjectManager::UpdateObjects(const DX::StepTimer& timer)
{
	// ����1 �͈�for��
	for (GameObjectPtr& object : m_objects)
	{
		object->Update(timer);
	}
}

/// <summary>
/// �X�V�����x�N�^�[�ɒǉ�
/// </summary>
void GameObjectManager::AcceptObjects()
{
	// �v�f�̈ړ�
	m_objects.splice(m_objects.end(), m_objectQueue);
}

/// <summary>
/// �ǉ������I�u�W�F�N�g������
/// </summary>
void GameObjectManager::DestroyObjects()
{
	// ����2 ������v����S�Ă̗v�f���폜
	m_objects.remove_if(std::mem_fn(&GameObject::IsInvalid));
}
