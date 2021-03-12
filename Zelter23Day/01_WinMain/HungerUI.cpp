#include "pch.h"
#include "HungerUI.h"
#include "Image.h"
HungerUI::HungerUI(const string& name, int x, int y) : UI(name)
{
	mX = x + 200;
	mY = y + 48;
	mRect = RectMake(mX, mY, 30, 30);
}

void HungerUI::Init()
{
	mEmptyGaugeImage = IMAGEMANAGER->FindImage(L"Statu_empty");
	mFullGaugeImage = IMAGEMANAGER->FindImage(L"Hunger_full");
	mIconImage = IMAGEMANAGER->FindImage(L"Hunger_icon");

	mHunger = 30;
}

void HungerUI::Release()
{
}

void HungerUI::Update()
{
	
}

void HungerUI::Render(HDC hdc)
{

	mEmptyGaugeImage->ScaleRender(hdc, mX, mY, 30, 30);
	mFullGaugeImage->Render(hdc, mX, mRect.bottom - mHunger, 0, 30 - mHunger, 30, mHunger);
	mIconImage->ScaleRender(hdc, mX + 7, mY + 7, 12 , 13);
}
