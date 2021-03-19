#pragma once
#include "UI.h"
class HungerUI : public UI
{
	Image* mEmptyGaugeImage;
	Image* mFullGaugeImage;
	Image* mIconImage;

	float mHunger;

public:
	HungerUI(const string& name, int x, int y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetHunger(int h) { mHunger = h; }
};

