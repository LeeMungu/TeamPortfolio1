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

	//무기좌표
	float mStartX;
	float mStartY;
	float mStartImageX;
	float mStartImageY;

	//무기 생성 시 플레이어 좌표
	float mStartPlayerX;
	float mStartPlayerY;
	//플레이어의 위치
	float mNowPlayerX;
	float mNowPlayerY;


	int mBullet;
	float mAngle; //총알 궤적?
	RECT mRect; //총 위치

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc, float cameraX, float cameraY)override;


	void SetPlayerPtr(Player* player) { mPlayer = player; }

};

