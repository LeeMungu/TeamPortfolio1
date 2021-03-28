#pragma once
#include "GameObject.h"
#include "Player.h"
#include "ObjectManager.h"


class Player;

class Bomb : public GameObject
{

	float mSizeX;
	float mSizeY;
	float mImageX;
	float mImageY;

	Image* mImage;

	bool mIsExplosion;
	bool mIsUse;

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;





};

