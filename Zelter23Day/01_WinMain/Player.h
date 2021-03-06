#pragma once
#include "GameObject.h"

class Image;
class Animation;

#define TileSize 32

enum class PlayerState
{
	walk,
	run,
	attack,
	die,
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

	float mSpeed;
	int mHP;
	int mThirst;
	int mHunger;
	int mStemina;

	PlayerState mPlayerState;

	


	//class Tile* mTileList[TileCountX][TileCountY];
	
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
};

