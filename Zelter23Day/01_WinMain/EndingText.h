#pragma once
#include "GameObject.h"

class Image;
class EndingText : public GameObject
{
	float mReduseSizeX;
	float mReduseSizeY;
	Image* mImage;
	int mIndexY;
public:
	EndingText(int indexY);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

