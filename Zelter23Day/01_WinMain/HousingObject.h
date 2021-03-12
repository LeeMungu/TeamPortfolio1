#pragma once
#include "GameObject.h"

class Tile;
class Image;
class HousingObject : public GameObject
{
	Image* mRoofSideImage;
	float mAlpha;

public:
	HousingObject(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

