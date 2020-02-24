//======================================================
// File Name	: GameObject.cpp
// Summary	: �Q�[���I�u�W�F�N�g�C���^�[�t�F�C�X
// Author		: Kyoya Sakamoto
//======================================================
#include <pch.h>

#include "GameObject.h"

/// <summary>
/// �R���X�g���N�^
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
/// �f�X�g���N
/// </summary>
GameObject::~GameObject()
{
}

/// <summary>
/// �����ɕϊ�
/// </summary>
void GameObject::Invalidate()
{
	m_isValid = false;
}

/// <summary>
/// �I�u�W�F�N�g����
/// </summary>
/// <param name="object"></param>
void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}
