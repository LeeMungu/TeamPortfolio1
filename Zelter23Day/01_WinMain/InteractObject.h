#pragma once
#include "GameObject.h"

#define InteractObjectSize 2

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
	//시작 타일 배열값
	int mTileIndexX, mTileIndexY;
	//입력해주는 Y값
	int mInputY;
	//무슨변수인가? 필요한 변수인가?
	bool mIsInteractive;
	wstring mImageKey;
	//인터렉트 렉트
	RECT mInteractRect;
public:
	InteractObject(const wstring imageKey, float x, float y, int hp, int tileCountX, int tileCountY);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	int GetHp()const { return mHp; }
	void SetHp(int hp) { mHp = hp; }
	wstring GetImageKey()const { return mImageKey; }
	
	int GetInputY()const { return mInputY; }
	int GetTileIndexX()const { return mTileIndexX; }
	int GetTileIndexY()const { return mTileIndexY; }
	int GetTileCountX()const { return mTileCountX; }
	int GetTileCountY()const { return mTileCountY; }

	RECT GetInteractRect()const { return mInteractRect; }

	bool GetIsInterRactive() { return GetIsInterRactive; }
	void SetIsInterRactive(bool interactive) { mIsInteractive = interactive; }
};

