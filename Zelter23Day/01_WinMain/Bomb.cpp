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
	//�갡 �����Ҷ� Ÿ�̸�
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
	mExplosion->InitFrameByStartEnd(0, 0, 6, 0, false);
	mExplosion->SetIsLoop(false);
	mExplosion->SetFrameUpdateTime(0.1f);
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
	//�������� ���� �������� �˼�����
	Timer = Time::GetInstance()->GetSceneTime() - SceneTimer;

	if (mIsExplosionAfter == false)
	{
		if (Timer >= 10.f)
		{
			mIsExplosion = true;
		}
		if (mIsExplosion == true)
		{
			//���߹���
			mRcExplosion = RectMakeCenter(mX, mY, 200, 200);
			SoundPlayer::GetInstance()->Play(L"BombSound", 0.8 * SoundPlayer::GetInstance()->GetEffectVolume());
			mIsExplosionAfter = true;

		}
	}
	if (mIsExplosionAfter == true)
	{
		
		mImage = IMAGEMANAGER->FindImage(L"Pistol_shoot");
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
