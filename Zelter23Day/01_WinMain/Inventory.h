#pragma once
#include "UI.h"
class Image;
struct BagSlot {
	float x;
	float y;
	Image* slotImage;
	RECT rect;
	//bool isSelected;
};
class Inventory : public UI
{
	Image* mBaseImage;
	bool mIsOpened;

	BagSlot mSlotList[5][2];

public:
	Inventory(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetOpened(bool b) { mIsOpened = b; }
};

