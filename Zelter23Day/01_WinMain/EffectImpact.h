#pragma once
#include "GameObject.h"

class Image;
class Animation;
class EffectImpact : public GameObject
{
public:
	Image* mImage;
	Animation* mAnimation;
	Animation* mCurrentAnimation;
	int mIndexX;
	int mIndexY;
	float mAngle;
	float mSpeed;
	float mGravity;


public:
	EffectImpact(int x, int y, int indexX, int indexY);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

