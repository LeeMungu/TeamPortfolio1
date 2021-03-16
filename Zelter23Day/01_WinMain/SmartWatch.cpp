#include "pch.h"
#include "SmartWatch.h"
#include "Image.h"
#include "PlayerHPUI.h"
#include "ThirstUI.h"
#include "HungerUI.h"
#include "SteminaUI.h"
#include "Player.h"
SmartWatch::SmartWatch(const string& name, int x, int y) : UI (name)
{
	mX = x;
	mY = y;

	mHour = 0;
	mMin = 0;
}

void SmartWatch::Init()
{
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

		if ((int)mSceneTime % 720 == 0 && mSceneTime > 1) {
			mDayTime = DayTime::night;
		}
	}
	else {
		mTimeBG = IMAGEMANAGER->FindImage(L"SW_night");
		if ((int)mSceneTime % 720 == 0 && mSceneTime > 1) {
			mDayTime = DayTime::morning;
		}
	}

	mPlayerHPUI->SetHP(mPlayer->GetHP());
	mThirstUI->SetThirst(mPlayer->GetThirst());
	mHungerUI->SetHunger(mPlayer->GetHunger());
	mSteminaUI->SetStemina(mPlayer->GetStemina());
	
	mSceneTime = Time::GetInstance()->GetSceneTime();
	
	mHour = (int)(mSceneTime / 60) % 60;
	mMin = (int)mSceneTime % 60;

	if (mHour == 0) mHour = 12;
	while (mHour >= 13) mHour -= 12;
}

void SmartWatch::Render(HDC hdc)
{
	mUIBaseImage->ScaleRender(hdc, mX + 102, mY + 12, 130, 100);

	mBaseImage->ScaleRender(hdc, mX, mY, 56*2, 64*2);
	mTimeBG->ScaleRender(hdc, mX + 14, mY + 18, 80, 83);
	mGlassDark->ScaleRender(hdc, mX + 14, mY + 18, 80, 83);
	mGlass->ScaleRender(hdc, mX + 14, mY + 18, 80, 83);
	
	wstring strDayTime;
	if (mDayTime == DayTime::morning) strDayTime = L"AM";
	else  strDayTime = L"PM";
	wstring strWatch = to_wstring(mHour/10 % 10) + to_wstring(mHour % 10)
		+ L" : " + to_wstring(mMin/10 % 10) + to_wstring(mMin % 10);
	D2DRenderer::GetInstance()
		->RenderText(30, 30, strDayTime.c_str(), 10);
	D2DRenderer::GetInstance()
		->RenderText(30, 50, strWatch.c_str(), 20);
}
