#pragma once
#include "GameObject.h"

class Image;
class NonInteractObject : public GameObject
{
	Image* mImage;
	
	int mIndexX;
	int mIndexY;
	wstring mImageKey;
public:
	NonInteractObject(const wstring imageKey, float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


	wstring GetImageKey()const { return mImageKey; }
};

