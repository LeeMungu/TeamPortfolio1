#include "pch.h"
#include "EffectImpact.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"


#define effectscale 2
EffectImpact::EffectImpact(wstring imagekey, int x, int y, int indexX)
{

	mImage = IMAGEMANAGER->GetInstance()->FindImage(L"Effect_impact");
	mImageKey = imagekey;
	mX = x;
	mY = y;	
	mSizeX = mImage->GetFrameWidth() * effectscale;
	mSizeY = mImage->GetFrameHeight() * effectscale;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mIndexX = indexX;
	mIndexY ;
	mAngle = Random::GetInstance()->RandomInt(70, 240) * 0.01f;
	mSpeed = Random::GetInstance()->RandomInt(100, 130);
	mGravity = 150.f;


	this->Init();
}

void EffectImpact::Init()
{
	wstring temp = mImageKey.substr(0, 3);
	
	if (temp == L"Ben") { mIndexY = 1; }
	else if (temp == L"Bus") { mIndexY = 4; }
	else if (temp == L"Cab") { mIndexY = 4; }
	else if (temp == L"Car") { mIndexY = 4; }
	else if (temp == L"Cha") { mIndexY = 1; }
	else if (temp == L"Clo") { mIndexY = 1; }
	else if (temp == L"Com") { mIndexY = 2; }
	else if (temp == L"Doo") { mIndexY = 1; }
	else if (temp == L"Dea") { mIndexY = 1; }
	else if (temp == L"Des") { mIndexY = 4; }
	else if (temp == L"dis") { mIndexY = 4; }
	else if (temp == L"Dol") { mIndexY = 3; }
	else if (temp == L"Dus") { mIndexY = 6; }
	else if (temp == L"Fan") { mIndexY = 6; }
	else if (temp == L"Han") { mIndexY = 2; }
	else if (temp == L"Mot") { mIndexY = 4; }
	else if (temp == L"Pla") { mIndexY = 1; }
	else if (temp == L"Ref") { mIndexY = 4; }
	else if (temp == L"Roc") { mIndexY = 0; }
	else if (temp == L"She") { mIndexY = 1; }
	else if (temp == L"Sho") { mIndexY = 2; }
	else if (temp == L"Sig") { mIndexY = 1; }
	else if (temp == L"Sof") { mIndexY = 5; }
	else if (temp == L"Suv") { mIndexY = 4; }
	else if (temp == L"Tab") { mIndexY = 1; }
	else if (temp == L"Toi") { mIndexY = 2; }
	else if (temp == L"Tre") { mIndexY = 1; }
	else if (temp == L"Tru") { mIndexY = 4; }
	else if (temp == L"Tv1") { mIndexY = 2; }
	else if (temp == L"Was") { mIndexY = 4; }
	else if (temp == L"Wat") { mIndexY = 4; }
	else if (temp == L"Wor") { mIndexY = 4; }
	else if (temp == L"Zom") { mIndexY = 3; }
	else if (temp == L"Bar") { mIndexY = 0; }
	else if (temp == L"Bol") { mIndexY = 4; }
	else { return; }
	
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, this);
}

void EffectImpact::Release()
{
}

void EffectImpact::Update()
{
	mX += cosf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mY -= sinf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mSpeed -= mGravity * Time::GetInstance()->DeltaTime();
	if (mSpeed <= 0)
	{
		mIsDestroy = true;
	}




	//if (mObjectLayerList.size() != NULL)
	//{

	//	//못찾았다. - 급한대로 예외처리함 후속 처리 필요
	//	if (mObjectLayerList.find(mImageKey) == mObjectLayerList.end())
	//	{
	//		mIndexY = 0;
	//		mIsDestroy = true;
	//		return;
	//	}
	//	if (mObjectLayerList.find(mImageKey)->second == TypeLayer::stone)
	//	{
	//		mIndexY = 0;
	//	}
	//	else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::wood)
	//	{
	//		mIndexY = 1;
	//	}
	//	else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::glass)
	//	{
	//		mIndexY = 2;
	//	}
	//	else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::fabric)
	//	{
	//		mIndexY = 3;
	//	}
	//	else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::Iron)
	//	{
	//		mIndexY = 4;
	//	}
	//	else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::Leather)
	//	{
	//		mIndexY = 5;
	//	}
	//	else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::plastic)
	//	{
	//		mIndexY = 6;
	//	}
	//}



}

void EffectImpact::Render(HDC hdc)
{
	//CameraManager::GetInstance()->GetMainCamera()->Render(hdc, mImage, mX, mY, mIndexX, mIndexY, mSizeX, mSizeY);

	CameraManager::GetInstance()->GetMainCamera()->FrameRender(hdc, mImage, mX, mY, mIndexX, mIndexY);
}
