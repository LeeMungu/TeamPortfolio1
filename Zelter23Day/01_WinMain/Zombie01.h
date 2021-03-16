#pragma once
#include "Enemy.h"
class Image;
class Tile;

enum class ZombieState : int
{
	Patrol,
	Chase,
	Attack,
	Die
};

class Zombie01 : public Enemy
{
	vector<vector<Tile*>> mTileList;
	float mAngle;
	float mDistance;
	ZombieState mZombistate;

	bool mIsSwichPos;
	float mSwithtime;

	RECT mAttackRect;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Patrol();
	void SearchPlayer();
	void Attack()override;

	void MovetoPlayer();

	void SetTileList(vector<vector<Tile*>> tilelist)
	{
		mTileList = tilelist;
	}

	RECT GetAttackRect() { return mAttackRect;}
	void SetAttackRect(RECT rect) { mAttackRect = rect; }
};

