#pragma once
#include "GameObject.h"

class Weapon : public GameObject
{
public:
	Weapon(const float x, float y, float sizeX, float sizeY);
	Image* mImage;

	int mBullet;
	float mAngle; //�Ѿ� ����?
	RECT mRect; //�� ��ġ

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;




};

