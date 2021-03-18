#pragma once
#include "GameObject.h"

enum class HouseLayer : int
{
	Floor,
	HouseWall,
	Roof
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
	//���ͷ�Ʈ ��Ʈ
	RECT mInteractRect;
	HouseLayer mHouselayer;

public:
	HousingObject(const wstring& name, float x, float y, int tileCountX, int tileCountY);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

