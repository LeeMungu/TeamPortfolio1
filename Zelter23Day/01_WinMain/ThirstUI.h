#pragma once
#include "UI.h"
class Image;
class ThirstUI : public UI
{
	Image* mEmptyGageImage;
	Image* mFullGageImage;
	Image* mIconImage;

	int mThirst;

public:
	ThirstUI(const string& name, int x, int y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

