#pragma once
#include "GameObject.h"
class Bullet :public GameObject
{
	class Image* mImage;
	float mSpeed;
	float mAngle;
	float mStartX;
	float mStartY;

public:
	Bullet(float x, float y, float mAngle);
	void Init()override;
	void Release()override;
	void Render(HDC hdc)override;
	void Update()override;
};

