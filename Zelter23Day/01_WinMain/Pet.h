#pragma once
#include "GameObject.h"
#include "Tile.h"

enum class PetState
{
	Idle,
	Follow,
	End
};

class Player;
class Animation;
class Pet : public GameObject
{
	Image* mImage;
	Player* mPlayer;
	PetState mPetState;
	vector<vector<Tile*>> mTileList;
	RECT mCollisionBox;

	float mDistance;
	float mFollowDistance;
	float mSpeed;
	float mAngle;

	bool mIsCheck;
	bool mIsTarget;


	Animation* mCurrentAnimation;
	Animation* mLeftMove;
	Animation* mRightMove;
	Animation* mUpMove;
	Animation* mDownMove;


public:
	Pet( float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	RECT GetCollisionBox() { return mCollisionBox; }
	void SetTileList(vector<vector<Tile*>> tilelist)
	{
		mTileList = tilelist;
	}

	void FindPlayer();
	void FollowPlayer();
};

