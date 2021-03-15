#pragma once
#include "GameObject.h"

class Mouse : public GameObject
{
	class Image* mImage;
	wstring mImageKey;
	vector<vector<class Tile*>> mTiles;
public:
	Mouse(wstring imageKey);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

