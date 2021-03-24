#include "pch.h"
#include "QuickSlot.h"
#include "Image.h"
QuickSlot::QuickSlot(const string& name) : UI(name)
{
}

void QuickSlot::Init()
{
	mX = WINSIZEX/2 + 50;
	mY = WINSIZEY - 64;

	for (int i = 0; i < 5; i++) {
		mSlotList[i].x = mX + i * 63 + 90;
		mSlotList[i].y = mY;
		mSlotList[i].tipCloseImg = IMAGEMANAGER->FindImage(L"QuickSlot_tip_close");
		mSlotList[i].tipOpenImg = IMAGEMANAGER->FindImage(L"QuickSlot_tip_open");
		mSlotList[i].slotImg = IMAGEMANAGER->FindImage(L"QuickSlot_slotBase");
		mSlotList[i].isSelected = false;
		mSlotList[i].rect = RectMake(mSlotList[i].x, mSlotList[i].y, 56, 58);
		mSlotList[i].isFill = false;
	}

	mBackImage = IMAGEMANAGER->FindImage(L"QuickSlot_back");
	mFrontImage = IMAGEMANAGER->FindImage(L"QuickSlot_front");

	mSelectedNum = 0;
}

void QuickSlot::Release()
{
}

void QuickSlot::Update()
{
	//¼ýÀÚÅ°·Î Äü½½·Ô ¼±ÅÃ
	if (Input::GetInstance()->GetKeyDown('1')) 
	{
		mSelectedNum = 1;
		if (mSlotList[0].isSelected == true) 
		{
			mSelectedNum = 0;
		}
		ItemManager::GetInstance()->QuickSlotRePositioning(1);
	}
	if (Input::GetInstance()->GetKeyDown('2')) 
	{
		mSelectedNum = 2;
		if (mSlotList[1].isSelected == true) 
		{
			mSelectedNum = 0;
		}
		ItemManager::GetInstance()->QuickSlotRePositioning(2);
	}
	if (Input::GetInstance()->GetKeyDown('3')) 
	{
		mSelectedNum = 3;
		if (mSlotList[2].isSelected == true) 
		{
			mSelectedNum = 0;
		}
		ItemManager::GetInstance()->QuickSlotRePositioning(3);
	}
	if (Input::GetInstance()->GetKeyDown('4')) 
	{
		mSelectedNum = 4;
		if (mSlotList[3].isSelected == true) 
		{
			mSelectedNum = 0;
		}
		ItemManager::GetInstance()->QuickSlotRePositioning(4);
	}
	if (Input::GetInstance()->GetKeyDown('5')) 
	{
		mSelectedNum = 5;
		if (mSlotList[4].isSelected == true) 
		{
			mSelectedNum = 0;
		}
		ItemManager::GetInstance()->QuickSlotRePositioning(5);
	}
 
	for (int i = 0; i < 5; i++)
	{
		if (i != (mSelectedNum - 1))
		{
			mSlotList[i].y = mY;
			mSlotList[i].isSelected = false;
		}
		else
		{
			mSlotList[i].y = mY - 20;
			mSlotList[i].isSelected = true;
		}
		mSlotList[i].rect = RectMake(mSlotList[i].x, mSlotList[i].y, 56, 58);
	}
	
}

void QuickSlot::Render(HDC hdc)
{
	mBackImage->ScaleRender(hdc, mX, mY, 240 * 2, 32 * 2);
	for (int i = 0; i < 5; i++) {
		mSlotList[i].slotImg->ScaleRender(hdc, mSlotList[i].x, mSlotList[i].y, 56, 58);
	
		if (mSlotList[i].isSelected == false)
			mSlotList[i].tipCloseImg->ScaleRender(hdc, mSlotList[i].x + 14, mSlotList[i].y - 3, 28, 18);
		else 
			mSlotList[i].tipOpenImg->ScaleRender(hdc, mSlotList[i].x + 14, mSlotList[i].y - 5, 28, 18);
	
	}
	mFrontImage->ScaleRender(hdc, mX + 76, mY + 30, 179 * 2, 16 * 2);

}
