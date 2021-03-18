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
		}
	}
	else {
		if (Input::GetInstance()->GetKeyDown('I')) {
			mX = -1000;
			mY = -1000;
			mIsOpened = false;
		}
	}
	
}

void Inventory::Render(HDC hdc)
{
	if (mIsOpened == true) mBaseImage->ScaleRender(hdc, mX, mY, 295*2, 255*2);
}
