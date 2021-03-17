#pragma once
#include "GameObject.h"
#include "Player.h"

class Player;
class Weapon : public GameObject
{
public:
	Weapon(const float x, float y, float sizeX, float sizeY);
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
	float mStartPlayerX;
	float mStartPlayerY;
	//�÷��̾��� ��ġ
	float mNowPlayerX;
	float mNowPlayerY;


	int mBullet;
	float mAngle; //�Ѿ� ����?
	RECT mRect; //�� ��ġ

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc, float cameraX, float cameraY)override;


	void SetPlayerPtr(Player* player) { mPlayer = player; }

};

