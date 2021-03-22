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
	//�����ϴ� Ÿ�� ����
	int mTileCountX, mTileCountY;
	//���� Ÿ�� �迭��
	int mTileIndexX, mTileIndexY;
	//�Է����ִ� Y��
	int mInputY;
	//���������ΰ�? �ʿ��� �����ΰ�?
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

	HouseLayer GethouseLayer() { return mHouselayer; }

};

