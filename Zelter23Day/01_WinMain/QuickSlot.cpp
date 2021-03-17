#include "pch.h"
#include "QuickSlot.h"
#include "Image.h"
QuickSlot::QuickSlot(const string& name, int x, int y) : UI(name)
{
	mX = x;
	mY = y;
}

void QuickSlot::Init()
{
	mTipOpenImg = IMAGEMANAGER->FindImage(L"QuickSlot_tip_open");
	mTipCloseImg = IMAGEMANAGER->FindImage(L"QuickSlot_tip_close");
	mSlotImg = IMAGEMANAGER->FindImage(L"QuickSlot_slotBase");
	
	mIsSelected = false;
}

void QuickSlot::Release()
{
}

void QuickSlot::Update()
{
}

void QuickSlot::Render(HDC hdc)
{
	mSlotImg->ScaleRender(hdc, mX, mY, 56, 58);

	if(mIsSelected == false) mTipCloseImg->ScaleRender(hdc, mX + 14, mY - 3, 28, 18);
	else mTipOpenImg->ScaleRender(hdc, mX + 14, mY - 5, 28, 18);
}
