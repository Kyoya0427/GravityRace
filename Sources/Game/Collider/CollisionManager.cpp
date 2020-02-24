//======================================================
// File Name	: CollisionManager.cpp
// Summary	: �R���W�����}�l�W���[
// Author		: Kyoya Sakamoto
//======================================================
#include "CollisionManager.h"
#include "BoxCollider.h"
#include "MoveBoxCollider.h"


#include <Utils\Utilities.h>

#include <Game\Object\GameObject.h>

#include "LineShape.h"
#include "RaycastHit.h"
#include "BoxShape.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;




/// <summary>
/// �R���X�g���N�^
/// </summary>
CollisionManager::CollisionManager()
	: m_colliderGroups()
	, m_collisionGroups()
{
}

/// <summary>
///�f�X�g���N�^ 
/// </summary>
CollisionManager::~CollisionManager()
{
}

/// <summary>
/// �Փ˂����o
/// </summary>
void CollisionManager::DetectCollision()
{
	for (const CollisionGroup& collisionGroup : m_collisionGroups)
	{
		if (collisionGroup.second.empty())
		{
			ColliderList& colliders = m_colliderGroups[collisionGroup.first];

			DetectCollision(colliders);
		}
		else
		{
			ColliderList& colliders1 = m_colliderGroups[collisionGroup.first];
			ColliderList& colliders2 = m_colliderGroups[collisionGroup.second];

			DetectCollision(colliders1, colliders2);
		}
	}
}

/// <summary>
///  �Փ˂����o
/// </summary>
/// <param name="colliders">�I�u�W�F�N�g</param>
void CollisionManager::DetectCollision(const ColliderList& colliders)
{
	colliders;
}

/// <summary>
///  �Փ˂����o
/// </summary>
/// <param name="colliders1">�I�u�W�F�N�g1</param>
/// <param name="colliders2">�I�u�W�F�N�g2</param>
void CollisionManager::DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2)
{
	for (const Collider* collider1 : colliders1)
	{
		for (const Collider* collider2 : colliders2)
		{
			RaycastHit hit;
			
			if (collider1->IsCollided(collider2,&hit))
			{
				collider1->HitContact(collider2,&hit);
				collider2->HitContact(collider1,&hit);
			}
		}
	}
}


bool CollisionManager::IsCollided(const MoveBoxCollider* collider1, const MoveBoxCollider* collider2, RaycastHit* raycastHit)
{
	collider1;
	collider2;
	raycastHit;
	return false;
}

bool CollisionManager::IsCollided(const BoxCollider* collider1, const BoxCollider* collider2, RaycastHit* raycastHit)
{
	collider1;
	collider2;
	raycastHit;
	return false;
}

bool CollisionManager::IsCollided(const BoxCollider* collider1, const MoveBoxCollider* collider2, RaycastHit* raycastHit)
{
	return IsCollided(collider2, collider1, raycastHit);
}


bool CollisionManager::IsCollided(const MoveBoxCollider * collider1, const BoxCollider * collider2, RaycastHit* raycastHit)
{
	
	LineShape line;
	BoxShape  box;

	line.posA = collider1->GetPosition();
	line.posB = collider1->GetPosition() + collider1->Getvelocity();

	box.pos = collider2->GetPosition();
	box.ext = collider2->GetSize() + collider1->GetSize();

	bool b =  HitCheck_Segment2AABB(line, box, raycastHit);


	
	return b;
}

bool CollisionManager::HitCheck_Line2AABB(const LineShape& line, const BoxShape& box, RaycastHit* hit)
{
	Vector3 p_l = line.posA;
	Vector3 dir_l = line.posB - line.posA;

	// �����x�N�g�����K��
	LineShape nLine = line;
	dir_l.Normalize();

	// ��������
	union
	{
		float f[3];
		XMFLOAT3 v;
	} p, d, min, max, tmp_t_norm, t_max_norm;

	p.v = p_l;
	d.v = dir_l;
	min.v = box.pos - box.ext*0.5f;
	max.v = box.pos + box.ext*0.5f;

	float tmp_t = -FLT_MAX;
	float t_max = FLT_MAX;
	for (int i = 0; i < 3; ++i)
		if (abs(d.f[i]) < FLT_EPSILON)
		{
			if (p.f[i] < min.f[i] || p.f[i] > max.f[i])
				return false; // �������Ă��Ȃ�
		}
		else
		{
			// �X���u�Ƃ̋������Z�o
			// t1���߃X���u�At2�����X���u�Ƃ̋���
			float odd = 1.0f / d.f[i];
			float t1 = (min.f[i] - p.f[i]) * odd;
			float t2 = (max.f[i] - p.f[i]) * odd;
			if (t1 > t2)
				std::swap(t1, t2);
			if (t1 > tmp_t) { tmp_t = t1; tmp_t_norm.v = Vector3::Zero; tmp_t_norm.f[i] = d.f[i] > 0 ? -1.0f : 1.0f; }
			if (t2 < t_max) { t_max = t2; t_max_norm.v = Vector3::Zero; t_max_norm.f[i] = d.f[i] < 0 ? -1.0f : 1.0f; }
			// �X���u�����`�F�b�N
			if (tmp_t >= t_max)
				return false;
		}
	if (hit)
	{
		hit->distNear = tmp_t;
		hit->distFar = t_max;
		hit->posNear = p_l + tmp_t * dir_l;
		hit->posFar = p_l + t_max * dir_l;
		hit->normNear = tmp_t_norm.v;
		hit->normFar = t_max_norm.v;
	}
	// �������Ă���
	return true;
}

bool CollisionManager::HitCheck_Line2AABB(const LineShape & line, const BoxShape & box, float * tA, float * tB, DirectX::SimpleMath::Vector3 * colPos)
{
	RaycastHit hit;
	HitCheck_Line2AABB(line, box, &hit);
	if (tA)
		*tA = hit.distNear;
	if (tB)
		*tB = hit.distFar;
	if (colPos)
		*colPos = hit.posNear;
	return true;
}


bool CollisionManager::HitCheck_Segment2AABB(const LineShape & line, const BoxShape & box, RaycastHit* hitout)
{
	RaycastHit hit;
	bool b = HitCheck_Line2AABB(line, box, &hit);
	if (hitout)
		*hitout = hit;
	float dist = Vector3::Distance(line.posA, line.posB);
	return b && 0 < hit.distFar && 0 < (dist - hit.distNear);
}

/// <summary>
/// �ǉ�
/// </summary>
/// <param name="groupName">�O���[�v��</param>
/// <param name="collider"></param>
void CollisionManager::Add(const std::string& groupName, Collider* collider)
{
	m_colliderGroups[groupName].push_back(collider);
}

/// <summary>
/// ��������O���[�v���擾
/// </summary>
/// <param name="groupName1">�O���[�v��</param>
/// <param name="groupName2">�O���[�v��</param>
void CollisionManager::AllowCollision(const std::string& groupName1, const std::string& groupName2)
{
	if (groupName1 == groupName2)
	{
		m_collisionGroups.push_back(std::make_pair(groupName1, ""));
	}
	else
	{
		m_collisionGroups.push_back(std::make_pair(groupName1, groupName2));
	}
}

