//======================================================
// File Name	: GameObjectManager.h
// Summary	: �Q�[���I�u�W�F�N�g�}�l�W���[
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <list>
#include <memory>
#include <SimpleMath.h>
#include <vector>
#include <functional>

#include "GameObject.h"

class GameObject;

class GameObjectManager final
{
using GameObjectPtr  = std::unique_ptr<GameObject>;
using GameObjectList = std::list<GameObjectPtr>;

private:
	//�ǉ���̃I�u�W�F�N�g
	GameObjectList m_objects;
	//�ǉ��O�̃I�u�W�F�N�g
	GameObjectList m_objectQueue;


public:
	GameObjectManager();

public:
	~GameObjectManager();

public:
	void Update(float elapsedTime);
	void Render();
	void Add(GameObjectPtr&& object);
	std::vector<GameObject*> Find(GameObject::ObjectID tag) const;
	std::vector<GameObject*> Find(std::function<bool(GameObject*)> predicate) const;

private:
	void UpdateObjects(float elapsedTime);
	void AcceptObjects();
	void DestroyObjects();
};