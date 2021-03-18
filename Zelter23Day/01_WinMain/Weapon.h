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
	float mAngle; //�Ѿ� ����?
	 //�� ��ġ

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


	void SetPlayerPtr(Player* player) { mPlayer = player; }

};

