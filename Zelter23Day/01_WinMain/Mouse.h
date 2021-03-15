#pragma once
#include "GameObject.h"

class Mouse : public GameObject
{
	class Image* mImage;
	vector<class Tile*> mTile;
public:
	Mouse(wstring imageKey);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

