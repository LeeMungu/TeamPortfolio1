#pragma once
#include "GameObject.h"

class Image;
class Animation;

class Bomb : public GameObject
{

	float SceneTimer;
	float Timer;

	float mSizeX;
	float mSizeY;
	float mImageX;
	float mImageY;

	Image* mImage;
	RECT mRcExplosion;

	bool mIsExplosion;
	bool mIsExplosionAfter;

	Animation* mExplosion;
	Animation* mCurrentAnimation;



public:
	Bomb(float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

