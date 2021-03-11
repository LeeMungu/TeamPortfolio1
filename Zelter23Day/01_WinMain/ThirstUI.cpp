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
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Thirst_icon", Resources(L"/01_UI/Gage_Icon_Thirst-resources.assets-996.bmp"), 7 * 2, 8 * 2, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Thirst_full", Resources(L"/01_UI/Gage_Fill_Thirst.bmp"), 15 * 2, 15 * 2, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Statu_empty", Resources(L"/01_UI/Gage01_Base-resources.assets-500.bmp"), 15 * 2, 15 * 2, true);
	
	mEmptyGageImage = IMAGEMANAGER->FindImage(L"Statu_empty");
	mFullGageImage = IMAGEMANAGER->FindImage(L"Thirst_full");
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
	mEmptyGageImage->Render(hdc, mX, mY);
	mFullGageImage->Render(hdc, mX, mRect.bottom - mThirst, 0, 30 - mThirst, 30, mThirst);
	mIconImage->Render(hdc, mX + 7, mY + 7);
}
