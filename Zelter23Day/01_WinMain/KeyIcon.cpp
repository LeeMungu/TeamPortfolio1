#include "pch.h"
#include "KeyIcon.h"
#include "Image.h"
KeyIcon::KeyIcon(const string& name) : UI(name)
{
	mX = -30;
	mY = 650;
}

void KeyIcon::Init()
{
	mBaseImage = IMAGEMANAGER->FindImage(L"BlackBase");

	mBagIconImage = IMAGEMANAGER->FindImage(L"Icon_bag");
	mCraftIconImage = IMAGEMANAGER->FindImage(L"Icon_craft");
	mTabletIconImage = IMAGEMANAGER->FindImage(L"Icon_tablet");
	mNameImage = IMAGEMANAGER->FindImage(L"Icon_name");

	mIKeyImage = IMAGEMANAGER->FindImage(L"Key_I");
	mCKeyImage = IMAGEMANAGER->FindImage(L"Key_C");
	mTKeyImage = IMAGEMANAGER->FindImage(L"Key_T");
}

void KeyIcon::Release()
{
}

void KeyIcon::Update()
{
}

void KeyIcon::Render(HDC hdc)
{
	mBaseImage->ScaleRender(hdc, mX + 80, mY + 13, 56 * 2, 55);
	mBaseImage->ScaleRender(hdc, mX + 80, mY + 83, 56 * 2, 55);
	mBaseImage->ScaleRender(hdc, mX + 80, mY + 153, 56 * 2, 55);

	mBagIconImage->ScaleRender(hdc, mX + 50, mY, 65, 65);
	mCraftIconImage->ScaleRender(hdc, mX + 50, mY + 70, 65, 65);
	mTabletIconImage->ScaleRender(hdc, mX + 50, mY + 140, 65, 65);

	mIKeyImage->ScaleRender(hdc, mX + 130, mY + 25, 40, 40);
	mCKeyImage->ScaleRender(hdc, mX + 130, mY + 95, 40, 40);
	mTKeyImage->ScaleRender(hdc, mX + 130, mY + 165, 40, 40);

	mNameImage->FrameRender(hdc, mX + 110, mY - 25, 0, 0);
	mNameImage->FrameRender(hdc, mX + 110, mY + 45, 1, 0);
	mNameImage->FrameRender(hdc, mX + 110, mY + 115, 2, 0);
}
