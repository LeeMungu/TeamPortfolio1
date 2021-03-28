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

	//������ǥ
	float mStartX;
	float mStartY;
	float mStartImageX;
	float mStartImageY;

	//���� ���� �� �÷��̾� ��ǥ
	//float mStartPlayerX;
	//float mStartPlayerY;

	bool mIsEqip;

	int mBullet;
	int mBullet2;
	int mBullet3;
	int mBullet4;
	int mBullet5;
	float mAngle; //�Ѿ� ����?
	float mAngle2;
	float mAngle3;
	float mAngle4;
	float mAngle5;

	 //�� ��ġ

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


	void SetPlayerPtr(Player* player) { mPlayer = player; }

	bool GetIsUse() { return mIsUse; }
	void SetIsUse(bool isUse) { mIsUse = isUse; }


};

