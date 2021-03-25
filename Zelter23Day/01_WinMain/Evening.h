#pragma once
#include "GameObject.h"
class Evening : public GameObject
{
	class Image* mImage;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

