#pragma once
#include "GameObject.h"

class Image;
class Animation;
class InteractObject : public GameObject
{
	Image* mImage;
	Animation* mCurrentAnimation;
	Animation* BeforeAnimation;
	Animation* AfterAnimation;
	bool isInteractive;


public:
	InteractObject(const string name, float x, float y, int hp);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

