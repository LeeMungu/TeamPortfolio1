#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Tile.h"
#include "MapToolScene.h"

Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mSpeed = 3.f;
	mDirection = Direction::Left;
}

void Player::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Player_run", Resources(L"/03_Player/Player_run.bmp"), 168*2, 156*2, 7, 4, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Player_walk", Resources(L"/03_Player/Player_walk.bmp"), 168*2, 156*2, 7, 4, true);
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"Player_attack", Resources(L"/03_Player/Player_attack.bmp"), 450*2, 86*2, 10, 2, true);
	mImage = IMAGEMANAGER->FindImage(L"Player_run");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	//Run Animation
	mUpRunAni = new Animation();
	mUpRunAni->InitFrameByStartEnd(1, 0, 6, 0, false);
	mUpRunAni->SetIsLoop(true);
	mUpRunAni->SetFrameUpdateTime(0.1f);

	mLeftRunAni = new Animation();
	mLeftRunAni->InitFrameByStartEnd(1, 2, 6, 2, false);
	mLeftRunAni->SetIsLoop(true);
	mLeftRunAni->SetFrameUpdateTime(0.1f);

	mRightRunAni = new Animation();
	mRightRunAni->InitFrameByStartEnd(1, 3, 6, 3, false);
	mRightRunAni->SetIsLoop(true);
	mRightRunAni->SetFrameUpdateTime(0.1f);

	mDownRunAni = new Animation();
	mDownRunAni->InitFrameByStartEnd(1, 1, 6, 1, false);
	mDownRunAni->SetIsLoop(true);
	mDownRunAni->SetFrameUpdateTime(0.1f);

	//Walk Animation
	mUpWalkAni = new Animation();
	mUpWalkAni->InitFrameByStartEnd(1, 0, 6, 0, false);
	mUpWalkAni->SetIsLoop(true);
	mUpWalkAni->SetFrameUpdateTime(0.1f);

	mLeftWalkAni = new Animation();
	mLeftWalkAni->InitFrameByStartEnd(1, 2, 6, 2, false);
	mLeftWalkAni->SetIsLoop(true);
	mLeftWalkAni->SetFrameUpdateTime(0.1f);

	mRightWalkAni = new Animation();
	mRightWalkAni->InitFrameByStartEnd(1, 3, 6, 3, false);
	mRightWalkAni->SetIsLoop(true);
	mRightWalkAni->SetFrameUpdateTime(0.1f);

	mDownWalkAni = new Animation();
	mDownWalkAni->InitFrameByStartEnd(1, 1, 6, 1, false);
	mDownWalkAni->SetIsLoop(true);
	mDownWalkAni->SetFrameUpdateTime(0.1f);

	//Attack Animation
	mLeftAttack = new Animation();
	mLeftAttack->InitFrameByStartEnd(0, 0, 9, 0, false);
	mLeftAttack->SetIsLoop(true);
	mLeftAttack->SetFrameUpdateTime(0.05f);

	mRightAttack = new Animation();
	mRightAttack->InitFrameByStartEnd(1, 1, 9, 1, false);
	mRightAttack->SetIsLoop(true);
	mRightAttack->SetFrameUpdateTime(0.05f);







	//Idle Animation
	mUpIdleAni = new Animation();
	mUpIdleAni->InitFrameByStartEnd(0, 0, 0, 0, false);
	mUpIdleAni->SetIsLoop(false);
	mUpIdleAni->SetFrameUpdateTime(0.1f);

	mDownIdleAni = new Animation();
	mDownIdleAni->InitFrameByStartEnd(0, 1, 0, 1, false);
	mDownIdleAni->SetIsLoop(false);
	mDownIdleAni->SetFrameUpdateTime(0.1f);

	mLeftIdleAni = new Animation();
	mLeftIdleAni->InitFrameByStartEnd(0, 2, 0, 2, false);
	mLeftIdleAni->SetIsLoop(false);
	mLeftIdleAni->SetFrameUpdateTime(0.1f);

	mRightIdleAni = new Animation();
	mRightIdleAni->InitFrameByStartEnd(0, 3, 0, 3, false);
	mRightIdleAni->SetIsLoop(false);
	mRightIdleAni->SetFrameUpdateTime(0.1f);

	mCurrentAnimation = mDownIdleAni;
}

void Player::Release()
{
	SafeDelete(mUpRunAni);
	SafeDelete(mLeftRunAni);
	SafeDelete(mRightRunAni);
	SafeDelete(mDownRunAni);

	SafeDelete(mUpWalkAni);
	SafeDelete(mLeftWalkAni);
	SafeDelete(mRightWalkAni);
	SafeDelete(mDownWalkAni);

	SafeDelete(mUpIdleAni);
	SafeDelete(mLeftIdleAni);
	SafeDelete(mRightIdleAni);
	SafeDelete(mDownIdleAni);

	SafeDelete(mRightAttack);
	SafeDelete(mLeftAttack);
}

void Player::Update()
{
	if (Input::GetInstance()->GetKey('W'))
	{
		if (_mousePosition.y > mY) 
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_walk");
			mCurrentAnimation = mDownWalkAni;
			mSpeed = 1.f;
		}
		else {
			mImage = IMAGEMANAGER->FindImage(L"Player_run");
			mCurrentAnimation = mUpRunAni;
			mSpeed = 3.f;
		}
		mY = mY - mSpeed;
		mCurrentAnimation->Play();
	}
	else if (Input::GetInstance()->GetKey('A'))
	{
		if (_mousePosition.x > mX)
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_walk");
			mCurrentAnimation = mRightWalkAni;
			mSpeed = 1.f;
		}
		else {
			mImage = IMAGEMANAGER->FindImage(L"Player_run");
			mCurrentAnimation = mLeftRunAni;
			mSpeed = 3.f;
		}
		mX = mX - mSpeed;
		mCurrentAnimation->Play();
	}
	else if (Input::GetInstance()->GetKey('D'))
	{
		if (_mousePosition.x < mX)
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_walk");
			mCurrentAnimation = mLeftWalkAni;
			mSpeed = 1.f;
		}
		else {
			mImage = IMAGEMANAGER->FindImage(L"Player_run");
			mCurrentAnimation = mRightRunAni;
			mSpeed = 3.f;
		}
		mX = mX + mSpeed;
		mCurrentAnimation->Play();
	}
	else if (Input::GetInstance()->GetKey('S'))
	{
		if (_mousePosition.y < mY)
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_walk");
			mCurrentAnimation = mUpWalkAni;
			mSpeed = 1.f;
		}
		else {
			mImage = IMAGEMANAGER->FindImage(L"Player_run");
			mCurrentAnimation = mDownRunAni;
			mSpeed = 3.f;
		}
		mY = mY + mSpeed;
		mCurrentAnimation->Play();
	}
	else if (Input::GetInstance()->GetKeyDown('F'))
	{
		if (_mousePosition.x < mX)
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_attack");
			mCurrentAnimation = mLeftAttack;
			mSpeed = 0.f;
		}
		else
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_attack");
			mCurrentAnimation = mRightAttack;
			mSpeed = 0.f;
		}
		mCurrentAnimation->Play();
	}

	else
	{
		if (mCurrentAnimation == mDownRunAni || mCurrentAnimation == mDownWalkAni) mCurrentAnimation = mDownIdleAni;
		else if (mCurrentAnimation == mUpRunAni || mCurrentAnimation == mUpWalkAni) mCurrentAnimation = mUpIdleAni;
		else if (mCurrentAnimation == mLeftRunAni || mCurrentAnimation == mLeftWalkAni) mCurrentAnimation = mLeftIdleAni;
		else if (mCurrentAnimation == mRightRunAni || mCurrentAnimation == mRightWalkAni) mCurrentAnimation = mRightIdleAni;
	}

	mCurrentAnimation->Update();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->
		FrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY());
	if (Input::GetInstance()->GetKey(VK_LSHIFT))
	{
		RenderRect(hdc, mRect);
	}
}
