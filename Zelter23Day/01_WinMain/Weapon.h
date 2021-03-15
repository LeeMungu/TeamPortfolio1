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
	//총엔 애니메이션이 필요없겠지?
	//Animation* mCurrentAnimation;

	int mBullet;
	float mAngle; //총알 궤적?
	RECT mRect; //총 위치

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;




};

