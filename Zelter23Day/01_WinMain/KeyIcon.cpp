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
	mBaseImage->ScaleRender(hdc, mX + 80, mY + 13, 56 * 2, 50);
	mBaseImage->ScaleRender(hdc, mX + 80, mY + 73, 56 * 2, 50);
	mBaseImage->ScaleRender(hdc, mX + 80, mY + 133, 56 * 2, 50);

	mBagIconImage->ScaleRender(hdc, mX + 50, mY, 60, 60);
	mCraftIconImage->ScaleRender(hdc, mX + 50, mY + 60, 60, 60);
	mTabletIconImage->ScaleRender(hdc, mX + 50, mY + 120, 60, 60);

	mIKeyImage->ScaleRender(hdc, mX + 130, mY + 20, 40, 40);
	mCKeyImage->ScaleRender(hdc, mX + 130, mY + 80, 40, 40);
	mTKeyImage->ScaleRender(hdc, mX + 130, mY + 140, 40, 40);
}
