#pragma once
#include "GameObject.h"
#include "Player.h"

class Image;
class Animation;

enum class WeaponState
{
	Idle,
	Attack,
};

class Weapon : public Player
{
	Image* mImage;
	//�ѿ� �ִϸ��̼��� �ʿ������?
	//Animation* mCurrentAnimation;

	int mBullet;
	float mAngle; //�Ѿ� ����?
	RECT mRect; //�� ��ġ

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;




};

