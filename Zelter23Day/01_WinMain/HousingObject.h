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
class Player;
class HousingObject : public GameObject
{
	Image* mImage;
	int mThick;
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
	Player* mPlayer;
	HouseLayer mHouselayer;
	float mAlpha;

	vector<RECT> mCollisionList;

	RECT mHouse01Rect1;
	RECT mHouse01Rect1_Left;
	RECT mHouse01Rect1_Top;
	RECT mHouse01Rect1_Right;
	RECT mHouse01Rect1_Bottom;
	RECT mHouse01Rect2;
	RECT mHouse01Rect2_Left;
	RECT mHouse01Rect2_Top;
	RECT mHouse01Rect2_Right;
	RECT mHouse01Rect2_Bottom;
	RECT mHouse04Rect1;
	RECT mHouse04Rect1_Left;
	RECT mHouse04Rect1_Top;
	RECT mHouse04Rect1_Right;
	RECT mHouse04Rect1_Bottom;
	RECT mHouse07Rect1;
	RECT mHouse07Rect1_Left;
	RECT mHouse07Rect1_Top;
	RECT mHouse07Rect1_Right;
	RECT mHouse07Rect1_Bottom;
	RECT mPoliceRect;
	RECT mPoliceRect_Left;
	RECT mPoliceRect_Top;
	RECT mPoliceRect_Right;
	RECT mPoliceRect_Bottom;
	RECT mShopRect1;
	RECT mShopRect1_Left;
	RECT mShopRect1_Top;
	RECT mShopRect1_Right;
	RECT mShopRect1_Bottom;
	RECT mShopRect2;
	RECT mShopRect2_Left;
	RECT mShopRect2_Top;
	RECT mShopRect2_Right;
	RECT mShopRect2_Bottom;

	vector<RECT> mZotherRect;
public:
	HousingObject(const wstring& name, float x, float y, int tileCountX, int tileCountY);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	float GetAlpha() { return mAlpha; }
	void SetAlpha(float alpha) { mAlpha = alpha; }
	
	vector<RECT> GetCollisionList() { return mCollisionList; }
	vector<RECT> GetZotherRect() { return mZotherRect; }
	wstring GetImageKey()const { return mImageKey; }


	int GetTileIndexX()const { return mTileIndexX; }
	int GetTileIndexY()const { return mTileIndexY; }
	int GetTileCountX()const { return mTileCountX; }
	int GetTileCountY()const { return mTileCountY; }

	HouseLayer GethouseLayer() { return mHouselayer; }

};

