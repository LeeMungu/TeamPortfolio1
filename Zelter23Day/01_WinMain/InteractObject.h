﻿#pragma once
#include "GameObject.h"

enum class TypeLayer
{
	철,
	나무,
	헝겁,
	end
};
class Image;
class InteractObject : public GameObject
{
	Image* mImage;
	int mHp;
	int mIndexX;
	int mIndexY;
	//차지하는 타일 갯수
	int mTileCountX, mTileCountY;
	//
	//무슨변수인가? 필요한 변수인가?
	bool mIsInteractive;
	wstring mImageKey;
public:
	InteractObject(const wstring imageKey, float x, float y, int hp, int tileCountX, int tileCountY);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetHp(int hp) { mHp = hp; }
	wstring GetImageKey()const { return mImageKey; }
};

