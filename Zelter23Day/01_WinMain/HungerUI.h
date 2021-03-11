#pragma once
#include "UI.h"
class HungerUI : public UI
{
	Image* mEmptyGageImage;
	Image* mFullGageImage;
	Image* mIconImage;

	int mHunger;

public:
	HungerUI(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

