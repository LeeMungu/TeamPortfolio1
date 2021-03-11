#include "pch.h"
#include "PlayerHPUI.h"
#include "Animation.h"
#include "Image.h"
#include "SmartWatch.h"
PlayerHPUI::PlayerHPUI(const string& name) : UI (name)
{
}

void PlayerHPUI::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Heart", Resources(L"/01_UI/Heart_Icon_Sheet-resources.assets-564.bmp"), 240*2, 20*2, 12, 1, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"CircleGage_empty", Resources(L"/01_UI/CircleGage_Status-resources.assets-697.bmp"), 75, 75, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"CircleGage_full", Resources(L"/01_UI/CircleGage_Status-Full.bmp"), 75, 75, true);
	
	mHeartImage = IMAGEMANAGER->FindImage(L"Heart");
	mEmptyGageImage = IMAGEMANAGER->FindImage(L"CircleGage_empty");
	mFullGageImage = IMAGEMANAGER->FindImage(L"CircleGage_full");

	mHeartAnimation = new Animation();
	mHeartAnimation->InitFrameByStartEnd(0, 0, 8, 0, true);
	mHeartAnimation->SetIsLoop(true);
	mHeartAnimation->SetFrameUpdateTime(0.1f);
	mHeartAnimation->Play();
	
	mX = 125;
	mY = 35;
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
	mEmptyGageImage->Render(hdc, mX, mY);
	mFullGageImage->Render(hdc, mX, mY);

	mHeartImage->FrameRender(hdc, mX + 17, mY + 17, mHeartAnimation->GetNowFrameX(), mHeartAnimation->GetNowFrameY());
}
