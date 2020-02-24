//======================================================
// File Name	: GameObject.h
// Summary	: �Q�[���I�u�W�F�N�g�C���^�[�t�F�C�X
// Author		: Kyoya Sakamoto
//======================================================
#pragma once


#include <SimpleMath.h>
#include <string>
#include <functional>

#include <Game\Collider\Collider.h>
#include <Game\Collider\RaycastHit.h>



class GameObject
{
public: 
	
	enum ObjectID
	{
		NONE,
		PLAYER,
		CAMERA,
		GROUND,
		BUILDING,
		CHECKPOINT
	};
	
private:
	bool        m_isValid;
	ObjectID    m_tag;


protected:
	DirectX::SimpleMath::Matrix     m_world;
	DirectX::SimpleMath::Vector3    m_position;
	DirectX::SimpleMath::Vector3    m_velocity;
	DirectX::SimpleMath::Quaternion m_rotation;
	DirectX::SimpleMath::Vector3    m_size;
	DirectX::SimpleMath::Vector3    m_collisionPos;
	DirectX::SimpleMath::Vector3    m_axis;
	float                           m_scale;

public:
	GameObject(ObjectID tag = ObjectID::NONE);

public:
	virtual ~GameObject();


public:
	virtual void Update(float elapsedTime) = 0;
	virtual void Render() = 0;

	virtual void HitContact(GameObject* object, RaycastHit* raycastHit = nullptr) = 0;
	


public:
	void Invalidate();
	bool IsValid() const;
	bool IsInvalid() const;

	//�Q�b�g�֐�
	const ObjectID GetTag() const;
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	const DirectX::SimpleMath::Vector3& GetVelosity() const;
	const DirectX::SimpleMath::Quaternion& GetRotation() const;
	const DirectX::SimpleMath::Vector3& GetSize() const;
	const DirectX::SimpleMath::Vector3& GetAxis() const;
	const float GetScale() const;
	
	//�Z�b�g�֐�
	void SetTag(const ObjectID tag);
	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity);
	void SetRotation(const DirectX::SimpleMath::Quaternion& rotation);
	void SetSize(const DirectX::SimpleMath::Vector3& size);
	void SetScale(const float scale);

	//vel��pos������
	void SetPosX(const float posX) { m_position.x = posX; }
	void SetPosY(const float posY) { m_position.y = posY; }
	void SetPosZ(const float posZ) { m_position.z = posZ; }

	void SetVelX(const float velX) { m_velocity.x = velX; }
	void SetVelY(const float velY) { m_velocity.y = velY; }
	void SetVelZ(const float velZ) { m_velocity.z = velZ; }

public:
	static void Destroy(GameObject* object);
};

/// <summary>
/// �L��
/// </summary>
/// <returns></returns>
inline bool GameObject::IsValid() const
{
	return m_isValid;
}

/// <summary>
/// ����
/// </summary>
/// <returns></returns>
inline bool GameObject::IsInvalid() const
{
	return !m_isValid;
}

/// <summary>
/// �^�O���擾
/// </summary>
/// <returns></returns>
inline const GameObject::ObjectID GameObject::GetTag() const
{
	return m_tag;
}

/// <summary>
/// ���W���擾
/// </summary>
/// <returns></returns>
inline const DirectX::SimpleMath::Vector3& GameObject::GetPosition() const
{
	return m_position;
}
/// <summary>
/// ���x���擾
/// </summary>
/// <returns></returns>
inline const DirectX::SimpleMath::Vector3 & GameObject::GetVelosity() const
{
	return m_velocity;
}

/// <summary>
/// ��]���擾
/// </summary>
/// <returns></returns>
inline const DirectX::SimpleMath::Quaternion & GameObject::GetRotation() const
{
	return m_rotation;
}

/// <summary>
/// �����蔻��̃T�C�Y���擾
/// </summary>
/// <returns></returns>
inline const DirectX::SimpleMath::Vector3 & GameObject::GetSize() const
{
	return m_size;
}

inline const DirectX::SimpleMath::Vector3 & GameObject::GetAxis() const
{
	return m_axis;
}

/// <summary>
/// �X�P�[�����擾
/// </summary>
/// <returns></returns>
inline const float GameObject::GetScale() const
{
	return m_scale;
}



/// <summary>
/// �^�O��ݒ�
/// </summary>
/// <param name="tag"></param>
inline void GameObject::SetTag(const ObjectID tag)
{
	m_tag = tag;
}

/// <summary>
/// ���W��ݒ�
/// </summary>
/// <param name="position"></param>
inline void GameObject::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_position = position;
}

/// <summary>
/// ���x��ݒ�
/// </summary>
/// <param name="velocity"></param>
inline void GameObject::SetVelocity(const DirectX::SimpleMath::Vector3 & velocity)
{
	m_velocity = velocity;
}

/// <summary>
/// ��]��ݒ�
/// </summary>
/// <param name="rotation"></param>
inline void GameObject::SetRotation(const DirectX::SimpleMath::Quaternion& rotation)
{
	m_rotation = rotation;
}

/// <summary>
/// �����蔻��̃T�C�Y��ݒ�
/// </summary>
/// <param name="size"></param>
inline void GameObject::SetSize(const DirectX::SimpleMath::Vector3 & size)
{
	m_size = size;
}

/// <summary>
/// �X�P�[���̐ݒ�
/// </summary>
/// <param name="scale"></param>
inline void GameObject::SetScale(const float scale)
{
	m_scale = scale;
}



