#pragma once
#include "GameObject.h"

enum class HouseLayer : int
{
	Roof,
	HouseWall,
	Floor
	
};

class Tile;
class Image;
class HousingObject : public GameObject
{
	Image* mImage;
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
	
	HouseLayer mHouselayer;
	float mAlpha;
	RECT mHouse01Rect1;
	RECT mHouse01Rect2;
public:
	HousingObject(const wstring& name, float x, float y, int tileCountX, int tileCountY);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	float GetAlpha() { return mAlpha; }
	void SetAlpha(float alpha) { mAlpha = alpha; }
	wstring GetImageKey()const { return mImageKey; }


	int GetTileIndexX()const { return mTileIndexX; }
	int GetTileIndexY()const { return mTileIndexY; }
	int GetTileCountX()const { return mTileCountX; }
	int GetTileCountY()const { return mTileCountY; }

};

