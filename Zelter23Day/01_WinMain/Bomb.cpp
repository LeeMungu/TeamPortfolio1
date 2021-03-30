#include "pch.h"
#include "Bomb.h"
#include "Image.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "WorkTable.h"
#include "Animation.h"
Bomb::Bomb(float x, float y)
{
	mX = x;
	mY = y;
	//얘가 시작할때 타이머
	SceneTimer = Time::GetInstance()->GetSceneTime();
	
}

void Bomb::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Bomb");
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mIsExplosion = false;
	mIsExplosionAfter = false;

	mExplosion = new Animation();
	mExplosion->InitFrameByStartEnd(0, 0, 5, 5, false);
	mExplosion->SetIsLoop(false);
	mExplosion->SetFrameUpdateTime(0.03f);
	mExplosion->SetCallbackFunc([this]() {mIsDestroy = true; });

	mCurrentAnimation = mExplosion;
	mCurrentAnimation->Play();
}

void Bomb::Release()
{
	SafeDelete(mExplosion);
}

void Bomb::Update()
{
	float cameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	float cameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;
	//생성된지 몇초 지났는지 알수있음
	Timer = Time::GetInstance()->GetSceneTime() - SceneTimer;

	if (mIsExplosionAfter == false)
	{
		if (Timer >= 5.f)
		{
			mIsExplosion = true;
		}
		if (mIsExplosion == true)
		{
			//폭발범위
			mRcExplosion = RectMakeCenter(mX, mY, 200, 200);
			SoundPlayer::GetInstance()->Play(L"BombSound", 0.8 * SoundPlayer::GetInstance()->GetEffectVolume());
			mIsExplosionAfter = true;

			Camera* camera = CameraManager::GetInstance()->GetMainCamera();
			camera->mIsShake = true;
		}
	}
	if (mIsExplosionAfter == true)
	{
		
		mImage = IMAGEMANAGER->FindImage(L"Explosion");
		mSizeX = 200;
		mSizeY = 200;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		mCurrentAnimation->Update();
	}



}

void Bomb::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);

}
