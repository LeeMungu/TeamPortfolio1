#pragma once
#include "GameObject.h"

class Image;
class Animation;
class NonInteractObject : public GameObject
{
	Image* mImage;

public:
	NonInteractObject(const string name, float x, float y);
	void Init()override;
	void Release()override;
	void Render(HDC hdc)override;
};

