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

}

void SmartWatch::Init()
{
	mBaseImage = IMAGEMANAGER->FindImage(L"SmarWatch_base");
	mGlassDark = IMAGEMANAGER->FindImage(L"SW_glass_dark");
	mGlass = IMAGEMANAGER->FindImage(L"SW_glass");
	mTimeBG = IMAGEMANAGER->FindImage(L"SW_morning");
	mUIBaseImage = IMAGEMANAGER->FindImage(L"BlackBase");

	mTensHourImg = IMAGEMANAGER->FindImage(L"SW_num");
	mUnitsHourImg = IMAGEMANAGER->FindImage(L"SW_num");
	mTensMinImg = IMAGEMANAGER->FindImage(L"SW_num");
	mUnitsMinImg = IMAGEMANAGER->FindImage(L"SW_num");
	mClock = IMAGEMANAGER->FindImage(L"SW_num");

	mHour = 0;
	mMin = 0;
	mDayTime = DayTime::morning;
	mAMPM = AMPM::PM;
	mIsFirstChange = false;
	mIsFstImgChange = false;

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
	mSceneTime = Time::GetInstance()->GetSceneTime();

	//Hour Min 나눠서 저장
	mHour = (int)(mSceneTime / 60) % 60;
	mMin = (int)mSceneTime % 60;

	//Hour 12시간 단위로 해줌
	while (mHour >= 12) mHour -= 12;

	//AM / PM 전환
	if (mHour == 0) {
		mHour = 12;
		if (mAMPM == AMPM::AM && mIsFirstChange == true) {
			mAMPM = AMPM::PM;
			mIsFirstChange = false;
		}
		else if (mAMPM == AMPM::PM && mIsFirstChange == true) {
			mAMPM = AMPM::AM;
			mIsFirstChange = false;
		}
	}
	else {
		mIsFirstChange = true;
	}

	//6시마다 Morning / Night 전환
	if (mHour == 6 && mAMPM == AMPM::PM && mIsFstImgChange == true) {
		mDayTime = DayTime::night;
		mTimeBG = IMAGEMANAGER->FindImage(L"SW_night");
	}
	else if (mHour == 6 && mAMPM == AMPM::AM && mIsFstImgChange == true) {
		mDayTime = DayTime::morning;
		mTimeBG = IMAGEMANAGER->FindImage(L"SW_morning");
	}
	else if (mHour != 6) {
		mIsFstImgChange = true;
	}

	//플레이어 정보 셋팅
	mPlayerHPUI->SetHP(mPlayer->GetHP());
	mThirstUI->SetThirst(mPlayer->GetThirst());
	mHungerUI->SetHunger(mPlayer->GetHunger());
	mSteminaUI->SetStemina(mPlayer->GetStemina());
	
}

void SmartWatch::Render(HDC hdc)
{
	mUIBaseImage->ScaleRender(hdc, mX + 102, mY + 12, 130, 100);

	mBaseImage->ScaleRender(hdc, mX, mY, 56*2, 64*2);
	mTimeBG->ScaleRender(hdc, mX + 14, mY + 18, 80, 83);
	mGlassDark->ScaleRender(hdc, mX + 14, mY + 18, 80, 83);
	mGlass->ScaleRender(hdc, mX + 14, mY + 18, 80, 83);
	
	wstring strDayTime = L"PM";
	if (mAMPM == AMPM::AM) strDayTime = L"AM";
	else strDayTime = L"PM";
	
	wstring strWatch = to_wstring(mHour/10 % 10) + to_wstring(mHour % 10)
		+ L" : " + to_wstring(mMin/10 % 10) + to_wstring(mMin % 10);
	D2DRenderer::GetInstance()
		->RenderText(30, 40, strDayTime.c_str(), 10);
	//D2DRenderer::GetInstance()->RenderText(30, 50, strWatch.c_str(), 20);
		
	mTensHourImg->ScaleFrameRender(hdc, mX + 12, mY + 50, mHour / 10 % 10, 0 , 25, 25);
	mUnitsHourImg->ScaleFrameRender(hdc, mX + 27, mY + 50, mHour % 10, 0, 25, 25);
	mClock->ScaleFrameRender(hdc, mX + 40, mY + 50, 10, 0, 25, 25);
	mTensMinImg->ScaleFrameRender(hdc, mX + 55, mY + 50, mMin / 10 % 10, 0, 25, 25);
	mTensMinImg->ScaleFrameRender(hdc, mX + 70, mY + 50, mMin % 10, 0, 25, 25);
}
