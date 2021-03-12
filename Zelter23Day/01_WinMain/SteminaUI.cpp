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
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Stemina_icon", Resources(L"/01_UI/Gage_Icon_Stemina.png"));
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Stemina_full", Resources(L"/01_UI/Gage_Fill_Stemina.png"));

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
	mEmptyGaugeImage->Render(hdc, mX, mY);
	mFullGaugeImage->Render(hdc, mX, mRect.bottom - mStemina, 0, 30 - mStemina, 30, mStemina);
	mIconImage->Render(hdc, mX + 7, mY + 7);
}
