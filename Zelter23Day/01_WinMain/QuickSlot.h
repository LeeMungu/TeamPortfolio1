#pragma once
#include "UI.h"
class Image;
struct Slot {
	float x;
	float y;
	Image* tipOpenImg;
	Image* tipCloseImg;
	Image* slotImg;
	bool isSelected;
};
class QuickSlot : public UI
{
	Image* mBackImage;
	Image* mFrontImage;

	Slot mSlotList[5];

	int mSelectedNum;
public:
	QuickSlot(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

