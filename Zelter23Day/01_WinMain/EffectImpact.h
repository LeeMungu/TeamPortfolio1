#pragma once
#include "GameObject.h"

class Image;
class Animation;
class EffectImpact : public GameObject
{
	Image* mImage;
	Animation* mAnimation;
public:
	EffectImpact(float x, float y, int startframeY);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

