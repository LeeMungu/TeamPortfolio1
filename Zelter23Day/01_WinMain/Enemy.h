#pragma once
#include "GameObject.h"


enum class ZombieState : int
{
	Patrol,
	Chase,
	Attack,
	Die
};
class Image;
class Player;
class Animation;
class Item;

class Enemy : public GameObject
{

public:
	enum class EnemyState
	{
		Idle,
		Move,
		Attack,
		Death
	};
	enum class Direction
	{
		Left,
		Right
	};

protected:
	Image* mImage;
	Player* mPlayer;
	Item* mItem;
	EnemyState mEnemyState;
	Direction mDirection;

	int mHp;
	int mSpeed;
	int mAttack;
	bool mTargeting;
	bool mTakenDamege;
	float mDelay;
	RECT mCollisionBox;
	RECT mAttackBox;

	Animation* mCurrentAnimation;
	Animation* mLeftIdle;
	Animation* mRightIdle;
	Animation* mLeftMove;
	Animation* mRightMove;
	Animation* mUpMove;
	Animation* mDownMove;
	Animation* mLeftAttack;
	Animation* mRightAttack;

public:
	Enemy();
	Enemy(float x, float y);

	virtual void Init()override = 0;
	virtual void Release()override = 0;
	virtual void Update()override = 0;
	virtual void Render(HDC hdc)override = 0;
	
	int GetAttack() { return mAttack; }
	RECT GetCollisionBox() { return mCollisionBox; }
	RECT GetAttackBox() { return mAttackBox; }
	int GetHP() { return mHp; }
	void SetHp(int hp) { mHp = hp; }
	void DropItem(Item item);
	void SetAnimation();
	virtual void Attack() {};


};

