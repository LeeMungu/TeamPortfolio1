#pragma once
#include "GameObject.h"
class Rain : public GameObject
{
	float mStartX;
	float mStartY;
	float mAngle;
	float mSpeed;
	float mLimitDistance;
	class Image* mImage;
public:
	Rain(float x, float y,float sizeX, float sizeY, float angle, float speed, float limitDistance);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

