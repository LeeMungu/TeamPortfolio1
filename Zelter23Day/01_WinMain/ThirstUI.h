#pragma once
#include "UI.h"
class Image;
class ThirstUI : public UI
{
	Image* mEmptyGaugeImage;
	Image* mFullGaugeImage;
	Image* mIconImage;

	int mThirst;

public:
	ThirstUI(const string& name, int x, int y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetThirst(int t) { mThirst = t; }
};

