#pragma once
#include "GameObject.h"

class Weapon : public GameObject
{
public:
	Weapon(const float x, float y, float sizeX, float sizeY);
	Image* mImage;

	int mBullet;
	float mAngle; //ÃÑ¾Ë ±ËÀû?
	RECT mRect; //ÃÑ À§Ä¡

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;




};

