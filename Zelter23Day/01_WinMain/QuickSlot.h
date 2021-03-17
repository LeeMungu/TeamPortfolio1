#pragma once
#include "UI.h"
class Image;
class QuickSlot : public UI
{
	Image* mTipOpenImg;
	Image* mTipCloseImg;
	Image* mSlotImg;

	bool mIsSelected;

public:
	QuickSlot(const string& name, int x, int y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

