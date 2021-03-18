#pragma once
#include "GameObject.h"
#include "Player.h"

class Player;
class Weapon : public GameObject
{
public:
	Weapon(const float x, float y, int imageX, int imageY);
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
	float mAngle; //ÃÑ¾Ë ±ËÀû?
	 //ÃÑ À§Ä¡

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


	void SetPlayerPtr(Player* player) { mPlayer = player; }

};

