#pragma once
#include "GameObject.h"

class Animation;
class BackGround : public GameObject
{
	class Image* mImage;
	Animation* mAnimation;
public:
	BackGround(const string& name, float x, float y);
	BackGround(const string& name, float x, float y, wstring key);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

