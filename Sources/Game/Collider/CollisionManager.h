//======================================================
// File Name	: CollisionManager.h
// Summary	: コリジョンマネジャー
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <vector>
#include <memory>
#include <SimpleMath.h>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Collider.h"
#include "LineShape.h"
#include "RaycastHit.h"
#include "BoxShape.h"

class GameObject;
class MoveBoxCollider;
class BoxCollider;


class CollisionManager 
{
using ColliderList       = std::vector<Collider*>;
using ColliderGroupList  = std::unordered_map<std::string, ColliderList>;
using CollisionGroup     = std::pair<std::string, std::string>;
using CollisionGroupList = std::list<CollisionGroup>;

enum ContactArea
{
	NO_CONTACT,
	TOP_CONTACT,
	BOTTOM_CONTACT,
	LEFT_CONTACT,
	RIGHT_CONTACT,
	FRONT_CONTACT,
	BACK_CONTACT,
	HIT_CONTACT
};

private:
	ColliderGroupList            m_colliderGroups;
	CollisionGroupList           m_collisionGroups;
	
public:
	CollisionManager();

public:
	~CollisionManager();

public:
	void Add(const std::string& groupName, Collider* collider);
	void AllowCollision(const std::string& groupName1, const std::string& groupName2);
	void DetectCollision();
	void DetectCollision(const ColliderList& colliders);
	void DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2);


public:
	static bool IsCollided(const MoveBoxCollider* collider1, const MoveBoxCollider* collider2, RaycastHit* raycastHit = nullptr);
	static bool IsCollided(const BoxCollider*     collider1, const BoxCollider*     collider2, RaycastHit* raycastHit = nullptr);
	static bool IsCollided(const BoxCollider*     collider1, const MoveBoxCollider* collider2, RaycastHit* raycastHit = nullptr);
	static bool IsCollided(const MoveBoxCollider* collider1, const BoxCollider*     collider2, RaycastHit* raycastHit = nullptr);


public:
	static bool HitCheck_Line2AABB(const LineShape& line, const BoxShape& box, RaycastHit* hit = nullptr);
	static bool HitCheck_Line2AABB(const LineShape& line, const BoxShape& box, float* tA = nullptr, float* tB = nullptr, DirectX::SimpleMath::Vector3* colPos = nullptr);
	static bool HitCheck_Segment2AABB(const LineShape & line, const BoxShape & box, RaycastHit* hitout);
};