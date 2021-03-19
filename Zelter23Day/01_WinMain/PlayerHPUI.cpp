#include "pch.h"
#include "PlayerHPUI.h"
#include "Animation.h"
#include "Image.h"
#include "SmartWatch.h"
PlayerHPUI::PlayerHPUI(const string& name, int x, int y) : UI (name)
{
	mX = x + 115;
	mY = y + 25;
}

void PlayerHPUI::Init()
{
	mHeartImage = IMAGEMANAGER->FindImage(L"Heart");
	mEmptyGaugeImage = IMAGEMANAGER->FindImage(L"CircleGage_empty");
	mFullGaugeImage = IMAGEMANAGER->FindImage(L"CircleGage_full");

	mHeartAnimation = new Animation();
	mHeartAnimation->InitFrameByStartEnd(0, 0, 8, 0, true);
	mHeartAnimation->SetIsLoop(true);
	mHeartAnimation->SetFrameUpdateTime(0.1f);
	mHeartAnimation->Play();
	
}

void PlayerHPUI::Release()
{
	SafeDelete(mHeartAnimation);
}

void PlayerHPUI::Update()
{
	mHeartAnimation->Update();
}

void PlayerHPUI::Render(HDC hdc)
{
	mEmptyGaugeImage->ScaleRender(hdc, mX, mY, 76, 76);
	//mFullGaugeImage->SetSize(Vector2(76, 76));
	//mFullGaugeImage->Render(hdc, mX, mRect.bottom - mHunger, 0, 30 - mHunger, 30, mHunger);
	//mFullGaugeImage->Render(hdc, mX - 8, mY - 8);

	int temp = 50;
	//hdc, 그릴 x , 그릴 y , 이미지 시작 x , 이미지 시작 y , 넓이, 높이 
	//mFullGaugeImage->Render(hdc, mX, mRect.bottom - temp, 0, 76 - temp, 76, temp);
	mFullGaugeImage->Render(hdc, mX, mY+(76-mHP), 0, 76-mHP, 76, mHP); //mHP가 풀일때가 76
	mHeartImage->ScaleFrameRender(hdc, mX + 17, mY + 17, mHeartAnimation->GetNowFrameX(), mHeartAnimation->GetNowFrameY(), 40, 40);
}
