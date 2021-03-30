#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Weapon;

enum class PlayerState
{
	idle,
	//walk,
	run,
	roll,
	attack,
	die,
	gun,
};
enum class Attacked
{
	left,
	right,
	top,
	down,
	lefttop,
	leftdown,
	righttop,
	rightdown
};
enum class Equipment
{
	normal,
	gun,
};

class Player : public GameObject
{

	

	Player* mPlayer;

	Image* mImage;
	Animation* mCurrentAnimation;

	Animation* mUpRunAni;
	Animation* mLeftRunAni;
	Animation* mRightRunAni;
	Animation* mDownRunAni;

	Animation* mUpWalkAni;
	Animation* mLeftWalkAni;
	Animation* mRightWalkAni;
	Animation* mDownWalkAni;

	Animation* mUpIdleAni;
	Animation* mLeftIdleAni;
	Animation* mRightIdleAni;
	Animation* mDownIdleAni;

	Animation* mLeftAttack;
	Animation* mRightAttack;

	Animation* mRightRoll;
	Animation* mLeftRoll;
	Animation* mUpRoll;
	Animation* mDownRoll;

	Animation* mDie;
	

	float mSpeed;
	int mHP;
	int mThirst;
	int mHunger;
	int mStemina;
	float mInvincibleCount;
	bool mIsInvincible;
	bool mIsKnockback;
	bool mIsDie;
	float mKnockbackDistance;
	float mAngle;
	float mTakenAngle;
	float mDash;

	bool mIsMousePosition;


	float mDashTime;

	PlayerState mPlayerState;
	Attacked mAttacked;

	RECT mCollisionBox;
	RECT mAttackBox;

	float mStartTime_hunger;
	float mStartTime_thirst;
	float mStartTime_stemina;
	float mStartTime_hp;
	
	SelectedItem mSelectedItem;
	Equipment mEquipment;


	//Weapon* weapon;

public:
	Player(const string& name, float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetSpeed(float speed) { mSpeed = speed; }


	int GetHP() { return mHP; }
	int GetThirst() { return mThirst; }
	int GetHunger() { return mHunger; }
	int GetStemina() { return mStemina; }
	bool GetIsDie() { return mIsDie; }
	float GetInvincibleCount() { return mInvincibleCount; }
	bool GetIsInvincible() { return mIsInvincible; }
	bool GetIsKnockback() {return mIsKnockback;	}
	RECT GetCollisionBox() { return mCollisionBox; }
	RECT GetAttackBox() { return mAttackBox; }
	Attacked GetAttacked() { return mAttacked; }
	PlayerState GetPlayerState() { return mPlayerState; }

	void SetIsInvincible(bool isInvincible) { mIsInvincible = isInvincible; }
	void SetAttacked(Attacked attacked) { mAttacked = attacked; }
	void SetHP(int hp) 
	{
		if (mHP > 0 && mHunger <= 100) mHP = hp;
		else if (mHP > 100) mHP = 100;
		else mHP = 0;
	}
	void SetThirst(int t) 
	{
		if (mThirst > 0 && mThirst <= 100) mThirst = t;
		else if (mThirst > 100) mThirst = 100;
		else mThirst = 0;
	}
	void SetHunger(int h) 
	{ 
		if (mHunger > 0 && mHunger <= 100) mHunger = h;
		else if (mHunger > 100) mHunger = 100;
		else mHunger = 0; 
	}
	void SetStemina(int s) 
	{
		if (mStemina > 0 && mStemina <= 100) mStemina = s;
		else if (mStemina > 100) mStemina = 100;
		else mStemina = 0;
	}
	void SetNoDamage(bool noDamage) { mIsInvincible = noDamage; }
		
	void PlayerCtrl();
	void AttackRectMake();//공격시 어택렉트생성
	void ExecuteKnockback(float angle, float force); // 충돌에서 넉백에 받아올 값
	void Knockback();//넉백상태 후처리
	void PlayerState();

	void WeaponUse(bool a);

	void EquipmentPlayerImage(int mode);//0넣으면 walk, 나머지 run
	void SetSelectedItem(SelectedItem s){ mSelectedItem = s; }
};

