#include "pch.h"
#include "SteminaUI.h"
#include "Image.h"
SteminaUI::SteminaUI(const string& name, int x, int y) : UI(name)
{
	mX = x + 200;
	mY = y + 80;
	mRect = RectMake(mX, mY, 30, 30);
}

void SteminaUI::Init()
{
	mEmptyGaugeImage = IMAGEMANAGER->FindImage(L"Statu_empty");
	mFullGaugeImage = IMAGEMANAGER->FindImage(L"Stemina_full");
	mIconImage = IMAGEMANAGER->FindImage(L"Stemina_icon");
	mStemina = 30;
}

void SteminaUI::Release()
{
}

void SteminaUI::Update()
{
}

void SteminaUI::Render(HDC hdc)
{
	mEmptyGaugeImage->ScaleRender(hdc, mX, mY, 30, 30);
	mFullGaugeImage->Render(hdc, mX, mRect.bottom - mStemina, 0, 30 - mStemina, 30, mStemina);
	mIconImage->ScaleRender(hdc, mX + 7, mY + 7, 12, 13);
}
