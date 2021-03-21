#pragma once
#include "GameObject.h"

class Image;
class Animation;
class EffectManager : public GameObject
{

public:
	Image* mImage;

	Animation* mAnimation;
	Animation* mCurrentAnimation;

public:
	void Init(wstring imagename, RECT temp, int frameStartX, int frameEndX, float frameTime);
	void Init()override {};
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

