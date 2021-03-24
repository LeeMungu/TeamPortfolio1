#pragma once
#include "UI.h"
class Image;
class Item;
struct BagSlot {
	float x;
	float y;
	Image* slotImage;
	Image* slotImage2;
	RECT rect;
	bool isFill;
};

class Inventory : public UI
{
	Image* mBaseImage;
	bool mIsOpened;

	BagSlot mSlotList[5][2];

	map<wstring, int> mItemList;
	//Item* mTestItem[5][2];

public:
	Inventory(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetOpened(bool b) { mIsOpened = b; }
	bool GetOpened() const { return mIsOpened; }
	BagSlot(*GetSlotList(void))[2]{	return mSlotList; }
};

