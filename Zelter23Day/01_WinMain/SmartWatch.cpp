#include "pch.h"
#include "SmartWatch.h"
#include "Image.h"
SmartWatch::SmartWatch(const string& name) : UI (name)
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SmarWatch_base", Resources(L"/01_UI/SmartWatch_Base.bmp"), 56*2, 64*2, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_glass_dark", Resources(L"/01_UI/SmartWatch_GlassDark1161.bmp"), 80, 83, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_glass", Resources(L"/01_UI/SmartWatch_GlassShine.bmp"), 80, 83, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_morning", Resources(L"/01_UI/Morning-resources.assets-2276.bmp"), 80, 83, false);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_night", Resources(L"/01_UI/Night-resources.assets-1833.bmp"), 80, 83, false);

	mBaseImage = IMAGEMANAGER->FindImage(L"SmarWatch_base");
	mGlassDark = IMAGEMANAGER->FindImage(L"SW_glass_dark");
	mGlass = IMAGEMANAGER->FindImage(L"SW_glass");
	mTimeBG = IMAGEMANAGER->FindImage(L"SW_morning");
	mX = 10;
	mY = 10;
}

void SmartWatch::Init()
{
}

void SmartWatch::Release()
{
}

void SmartWatch::Update()
{
}

void SmartWatch::Render(HDC hdc)
{
	mBaseImage->Render(hdc, mX, mY);
	mTimeBG->Render(hdc, mX + 14, mY + 18);
	mGlassDark->Render(hdc, mX + 14, mY + 18);
	mGlass->AlphaRender(hdc, mX + 14, mY + 18, 0.3f);
}
