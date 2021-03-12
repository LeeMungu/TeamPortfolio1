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
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Heart", Resources(L"/01_UI/Heart_Icon.png"), 12, 1);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"CircleGage_empty", Resources(L"/01_UI/CircleGage_Status.png"));
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"CircleGage_full", Resources(L"/01_UI/CircleGage_Status-Full.png"));
	
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
	mFullGaugeImage->ScaleRender(hdc, mX, mY, 76, 76);
	mHeartImage->ScaleFrameRender(hdc, mX + 17, mY + 17, mHeartAnimation->GetNowFrameX(), mHeartAnimation->GetNowFrameY(), 40, 40);
}
