//======================================================
// File Name	: Player.h
// Summary	: �v���C���[�}�l�W���[
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

#include <Framework\DeviceResources.h>
#include <Framework\StepTimer.h>

#include <SimpleMath.h>
#include <Keyboard.h>
#include <Model.h>
#include <CommonStates.h>
#include <GeometricPrimitive.h>

#include <Game\Camera\TPSCamera.h>

#include <Game\Object\GameObject.h>
#include <Game\Collider\MoveBoxCollider.h>



class IPlayer;
class Standing;
class Running;
class Jumping;
class Floating;
class Agravity;

class Player :public GameObject
{
public:
	enum GravityState
	{
		GRAVITATION,
		AGRAVITY,
	};

	enum Contact
	{
		NO_CONTACT,
		HIT_CONTACT
	};
	
public:
	Player();
	~Player();

	//�X�V
	void Update(float elapsedTime) override;
	void Render() override;
	
	
	void HitContact(GameObject* object,RaycastHit* raycastHit = nullptr)override;

private:
	//�L�[�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker      m_keyBoardStateTracker;	
	//���f���f�[�^
	std::unique_ptr<DirectX::Model>              m_model;
	//�����蔻��
	std::unique_ptr<MoveBoxCollider>             m_collider;
	//�v���C���[
	IPlayer*                                     m_player;
	//���̏��
	int                                          m_isContact;
	int                                          m_isGravityState;
	//���C�L���X�g�q�b�g���擾
	RaycastHit									 m_raycastHit;

	float										 m_gravity;
	float                                        m_energy;
	static constexpr float MOVE_SPEED = 0.5f;

private:
	//Standing
	std::unique_ptr<Standing> m_standing;
	//Running;
	std::unique_ptr<Running>  m_running;
	//Jumping
	std::unique_ptr<Jumping>  m_jumping;
	//Floating
	std::unique_ptr<Floating> m_floating;
	//Agravity
	std::unique_ptr<Agravity> m_agravity;


//�Q�b�^�[
public:
	//�L�[�{�[�h�擾
	DirectX::Keyboard::KeyboardStateTracker GetKeyboardTracker() { return m_keyBoardStateTracker; }

	//�X�e�C�g�ύX
public:
	void ChangeStandingState() { m_player = (IPlayer*)m_standing.get(); }
	void ChangeRunningState()  { m_player = (IPlayer*)m_running.get(); }
	void ChangeJumpingState()  { m_player = (IPlayer*)m_jumping.get(); }
	void ChangeFloatingState() { m_player = (IPlayer*)m_floating.get(); }
	void ChaneAgravityState()  { m_player = (IPlayer*)m_agravity.get(); }

public:
	int GetContact()     { return m_isContact; }
	int GetIsGravityState()  { return m_isGravityState; }


	RaycastHit GetRaycastHit() { return m_raycastHit; }

	float GetEnergy() { return m_energy; }
	float GetEnergyLate() { return m_energy / 5; }

	void ChangeGravitation() { m_isGravityState = GRAVITATION; }
	void ChangeAgravity()    { m_isGravityState = AGRAVITY; }

	void ChangeNoContact()        { m_isContact = NO_CONTACT; }
	void ChangeHitContact()       { m_isContact = HIT_CONTACT; }
};
