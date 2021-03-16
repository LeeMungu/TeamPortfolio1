#pragma once
#include "Enemy.h"
class Image;
class Tile;
class Zombie01 : public Enemy
{
	vector<vector<Tile*>> mTileList;
	float mAngle;
	float mDistance;
	bool mTest;
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
};

