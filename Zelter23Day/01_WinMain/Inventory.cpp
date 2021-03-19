#include "pch.h"
#include "Inventory.h"
#include "Image.h"
Inventory::Inventory(const string & name) : UI(name)
{
}

void Inventory::Init()
{
	mX = -1000;
	mY = -1000;

	mBaseImage = IMAGEMANAGER->FindImage(L"Inventory_base");
	mIsOpened = false;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			mSlotList[i][j].x = mX + i * 60 + 170;
			mSlotList[i][j].y = mY + j * 60 + 250;
			mSlotList[i][j].slotImage = IMAGEMANAGER->FindImage(L"Inventory_slot");
			mSlotList[i][j].rect = RectMake(mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
		}
	}
}

void Inventory::Release()
{
}

void Inventory::Update()
{
	//임시로 위치 조정해서 열고 닫는것처럼 보임
	if (mIsOpened == false) {
		if (Input::GetInstance()->GetKeyDown('I')) {
			mX = WINSIZEX / 2 - 30;
			mY = WINSIZEY - 255 * 2;
			mIsOpened = true;

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					mSlotList[i][j].x = mX + i * 60 + 170;
					mSlotList[i][j].y = mY + j * 60 + 250;
					mSlotList[i][j].rect = RectMake(mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
				}
			}
		}
	}
	else {
		if (Input::GetInstance()->GetKeyDown('I')) {
			mX = -1000;
			mY = -1000;
			mIsOpened = false;

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					mSlotList[i][j].x = mX + i * 60 + 170;
					mSlotList[i][j].y = mY + j * 60 + 250;
					mSlotList[i][j].rect = RectMake(mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
				}
			}
		}
	}
	
}

void Inventory::Render(HDC hdc)
{
	if (mIsOpened == true) {
		mBaseImage->ScaleRender(hdc, mX, mY, 295 * 2, 255 * 2);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				mSlotList[i][j].slotImage->ScaleRender(hdc, mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
			}
		}
	}
}
