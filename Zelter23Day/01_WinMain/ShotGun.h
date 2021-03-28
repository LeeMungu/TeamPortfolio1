#pragma once
#include "GameObject.h"
#include "Player.h"
#include "ObjectManager.h"


class Player;

class ShotGun : public GameObject
{
	bool mIsUse;

public:
	ShotGun(const string& name, const float x, float y, int imageX, int imageY);
	Image* mImage;

	Player* mPlayer;
	float mImageX;
	float mImageY;
	int mDamege;

	//¹«±âÁÂÇ¥
	float mStartX;
	float mStartY;
	float mStartImageX;
	float mStartImageY;

	//¹«±â »ý¼º ½Ã ÇÃ·¹ÀÌ¾î ÁÂÇ¥
	//float mStartPlayerX;
	//float mStartPlayerY;

	bool mIsEqip;

	int mBullet;
	int mBullet2;
	int mBullet3;
	int mBullet4;
	int mBullet5;
	float mAngle; //ÃÑ¾Ë ±ËÀû?
	float mAngle2;
	float mAngle3;
	float mAngle4;
	float mAngle5;

	 //ÃÑ À§Ä¡

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


	void SetPlayerPtr(Player* player) { mPlayer = player; }

	bool GetIsUse() { return mIsUse; }
	void SetIsUse(bool isUse) { mIsUse = isUse; }


};

