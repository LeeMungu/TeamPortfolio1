#include "pch.h"
#include "ThirstUI.h"
#include "Image.h"
ThirstUI::ThirstUI(const string& name, int x, int y) : UI(name)
{
	mX = x + 200;
	mY = y + 15;
	mRect = RectMake(mX, mY, 30, 30);
}

void ThirstUI::Init()
{
	mEmptyGaugeImage = IMAGEMANAGER->FindImage(L"Statu_empty");
	mFullGaugeImage = IMAGEMANAGER->FindImage(L"Thirst_full");
	mIconImage = IMAGEMANAGER->FindImage(L"Thirst_icon");

	mThirst = 30;
}

void ThirstUI::Release()
{
}

void ThirstUI::Update()
{
}

void ThirstUI::Render(HDC hdc)
{
	mEmptyGaugeImage->ScaleRender(hdc, mX, mY, 30, 30);
	mFullGaugeImage->Render(hdc, mX, mRect.bottom - mThirst, 0, 30 - mThirst, 30, mThirst);
	mIconImage->ScaleRender(hdc, mX + 7, mY + 7, 12, 13);
}
