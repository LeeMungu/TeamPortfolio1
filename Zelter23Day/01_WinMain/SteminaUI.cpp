#include "pch.h"
#include "SteminaUI.h"
#include "Image.h"
SteminaUI::SteminaUI(const string& name, int x, int y) : UI(name)
{
	mX = x + 200;
	mY = y + 80;
}

void SteminaUI::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Stemina_icon", Resources(L"/01_UI/Gage_Icon_Stemina.bmp"), 7 * 2, 8 * 2, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Stemina_full", Resources(L"/01_UI/Gage_Fill_Stemina.bmp"), 15 * 2, 15 * 2, true);

	mEmptyGageImage = IMAGEMANAGER->FindImage(L"Statu_empty");
	mFullGageImage = IMAGEMANAGER->FindImage(L"Stemina_full");
	mIconImage = IMAGEMANAGER->FindImage(L"Stemina_icon");
}

void SteminaUI::Release()
{
}

void SteminaUI::Update()
{
}

void SteminaUI::Render(HDC hdc)
{
	mEmptyGageImage->Render(hdc, mX, mY);
	mFullGageImage->Render(hdc, mX, mY);
	mIconImage->Render(hdc, mX + 7, mY + 7);
}
