#include "pch.h"
#include "SmartWatch.h"
#include "Image.h"
#include "PlayerHPUI.h"
#include "ThirstUI.h"
#include "HungerUI.h"
#include "SteminaUI.h"
SmartWatch::SmartWatch(const string& name, int x, int y) : UI (name)
{
	mX = x;
	mY = y;
}

void SmartWatch::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SmarWatch_base", Resources(L"/01_UI/SmartWatch_Base.bmp"), 56 * 2, 64 * 2, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_glass_dark", Resources(L"/01_UI/SmartWatch_GlassDark1161.bmp"), 80, 83, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_glass", Resources(L"/01_UI/SmartWatch_GlassShine.bmp"), 80, 83, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_morning", Resources(L"/01_UI/Morning-resources.assets-2276.bmp"), 80, 83, false);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_night", Resources(L"/01_UI/Night-resources.assets-1833.bmp"), 80, 83, false);

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"BlackBase", Resources(L"/01_UI/black_base_status.bmp"), 130, 101, true);

	mBaseImage = IMAGEMANAGER->FindImage(L"SmarWatch_base");
	mGlassDark = IMAGEMANAGER->FindImage(L"SW_glass_dark");
	mGlass = IMAGEMANAGER->FindImage(L"SW_glass");
	mTimeBG = IMAGEMANAGER->FindImage(L"SW_morning");
	mUIBaseImage = IMAGEMANAGER->FindImage(L"BlackBase");


	

	mDayTime = DayTime::morning;

	mPlayerHPUI = new PlayerHPUI("PlayerHPUI", mX, mY);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mPlayerHPUI);

	mThirstUI = new ThirstUI("ThirstUI", mX, mY);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mThirstUI);

	mHungerUI = new HungerUI("HungerUI", mX, mY);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mHungerUI);
	
	mSteminaUI = new SteminaUI("SteminaUI", mX, mY);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mSteminaUI);

}

void SmartWatch::Release()
{
}

void SmartWatch::Update()
{
	if (mDayTime == DayTime::morning) {
		mTimeBG = IMAGEMANAGER->FindImage(L"SW_morning");
	}
	else {
		mTimeBG = IMAGEMANAGER->FindImage(L"SW_night");
	}
}

void SmartWatch::Render(HDC hdc)
{
	mUIBaseImage->AlphaRender(hdc, mX + 102, mY + 12, 0.7f);

	mBaseImage->Render(hdc, mX, mY);
	mTimeBG->Render(hdc, mX + 14, mY + 18);
	mGlassDark->Render(hdc, mX + 14, mY + 18);
	mGlass->AlphaRender(hdc, mX + 14, mY + 18, 0.3f);
}
