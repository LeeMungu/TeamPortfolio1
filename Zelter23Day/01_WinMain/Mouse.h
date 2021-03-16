#pragma once
#include "GameObject.h"

class Mouse : public GameObject
{
	class Image* mImage;
	wstring mImageKey;
	//�ʿ��Ѱ�?
	vector<vector<class Tile*>> mTiles;
	ObjectLayer mObjectType;
	
	//interactObject�϶� �ʿ�
	int mTileCountY;
	int mHpMax;
public:
	Mouse(wstring imageKey, ObjectLayer objectLayer);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetHpMax(int hpMax) { mHpMax = hpMax; }
	void SetTileCountY(int tileCountY) { mTileCountY = tileCountY; }
};

