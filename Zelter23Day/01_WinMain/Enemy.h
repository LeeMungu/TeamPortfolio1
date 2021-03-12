#pragma once
#include "GameObject.h"



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
	Enemy(float x, float y);
	virtual void Init()override = 0;
	virtual void Release()override = 0;
	virtual void Update()override = 0;
	virtual void Render(HDC hdc)override = 0;
	
	int GetAttack() { return mAttack; }
	void SetHp(int hp) { mHp = hp; }
	void DropItem(Item item);
	void SetAnimation();
	virtual void Attack() {};

};

