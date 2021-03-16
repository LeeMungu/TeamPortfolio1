#pragma once
#include "GameObject.h"

class Image;
class Animation;

enum class PlayerState
{
	idle,
	//walk,
	run,
	roll,
	attack,
	die,
};
enum class Attacked
{
	left,
	right,
	top,
	bottom
};
class Player : public GameObject
{
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

	float mSpeed;
	int mHP;
	int mThirst;
	int mHunger;
	int mStemina;
	float mInvincibleCount;
	bool mIsInvincible;
	bool mIsKnockback;
	float mDash;

	PlayerState mPlayerState;
	Attacked mAttacked;

	
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
	float GetInvincibleCount() { return mInvincibleCount; }
	bool GetIsInvincible() { return mIsInvincible; }
	bool GetIsKnockback() {return mIsKnockback;	}
	Attacked GetAttacked() { return mAttacked; }

	void SetAttacked(Attacked attacked) { mAttacked = attacked; }
	void SetHP(int hp) { mHP = hp; }
	void SetNoDamage(bool noDamage) { mIsInvincible = noDamage; }
	void SetmIsKnockback(bool knockback) { mIsKnockback = knockback; }

	void PlayerCtrl();
};

