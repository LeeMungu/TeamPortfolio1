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

	mHP = 100;
	mThirst = 30;
	mHunger = 30;
	mStemina = 30;

	mAngle = 0;
}

void Player::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Player_run");
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mIsNoDamage = true;
	mNoDamageCount = 0;

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
	mLeftAttack->SetIsLoop(false);
	mLeftAttack->SetFrameUpdateTime(0.05f);

	mRightAttack = new Animation();
	mRightAttack->InitFrameByStartEnd(1, 1, 9, 1, false);
	mRightAttack->SetIsLoop(false);
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
	mLeftIdleAni->SetIsLoop(true);
	mLeftIdleAni->SetFrameUpdateTime(0.1f);

	mRightIdleAni = new Animation();
	mRightIdleAni->InitFrameByStartEnd(0, 3, 0, 3, false);
	mRightIdleAni->SetIsLoop(true);
	mRightIdleAni->SetFrameUpdateTime(0.1f);

	mCurrentAnimation = mDownIdleAni;
	mPlayerState = PlayerState::idle;
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
	// mAngle += 5;
	PlayerCtrl();

	mCurrentAnimation->Update();
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Player::Render(HDC hdc)
{
	mImage->SetAngle(mAngle);

	CameraManager::GetInstance()->GetMainCamera()->
		ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);
	if (Input::GetInstance()->GetKey(VK_LSHIFT))
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect);
		//RenderRect(hdc, mRect);
	}
}

void Player::PlayerCtrl() {
	//플리이어 포인트 위치
	POINT playerPoint = CameraManager::GetInstance()->GetMainCamera()->GetPoint(GetX(), GetY());

	if (mPlayerState != PlayerState::attack) 
	{
		//달리는 상태에서만 구르기
		if (mPlayerState == PlayerState::run) {
			if (Input::GetInstance()->GetKeyDown(VK_RBUTTON)) { 
				mPlayerState = PlayerState::roll;
				mSpeed = 5.f;
			}
		}
		/*
		if (mPlayerState == PlayerState::roll) {
			mAngle += 5;
			if (mAngle >= 360) {
				mPlayerState = PlayerState::run;
			}
		}
		*/

		//위아래 이동
		if (Input::GetInstance()->GetKey('W'))
		{
			if (mPlayerState != PlayerState::roll) {
				mPlayerState = PlayerState::run;

				if (_mousePosition.y > playerPoint.y)
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
			}
			else {
				mAngle += 5;
				mSpeed = 5.f;
				if (mAngle >= 360) {
					mAngle = 0;
					mPlayerState = PlayerState::run;
				}
			}
			mY = mY - mSpeed;
			mCurrentAnimation->Play();
		}
		else if (Input::GetInstance()->GetKey('S'))
		{
			if (mPlayerState != PlayerState::roll) {
				mPlayerState = PlayerState::run;

				if (_mousePosition.y < playerPoint.y)
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
			}
			else {
				mAngle += 5;
				mSpeed = 5.f;
				if (mAngle >= 360) {
					mAngle = 0;
					mPlayerState = PlayerState::run;
				}
			}
			mY = mY + mSpeed;
			mCurrentAnimation->Play();
		}

		if (Input::GetInstance()->GetKeyUp('W') || Input::GetInstance()->GetKeyUp('S')) {
			mPlayerState = PlayerState::idle;

			if (mCurrentAnimation == mDownRunAni || mCurrentAnimation == mDownWalkAni) mCurrentAnimation = mDownIdleAni;
			else if (mCurrentAnimation == mUpRunAni || mCurrentAnimation == mUpWalkAni) mCurrentAnimation = mUpIdleAni;
		}

		//좌우이동
		if (Input::GetInstance()->GetKey('A'))
		{
			if (mPlayerState != PlayerState::roll) {
				mPlayerState = PlayerState::run;

				if (_mousePosition.x > playerPoint.x)
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
			}
			else {
				mAngle += 5;
				mSpeed = 5.f;
				if (mAngle >= 360) {
					mAngle = 0;
					mPlayerState = PlayerState::run;
				}
			}
			mX = mX - mSpeed;
			mCurrentAnimation->Play();
		}
		else if (Input::GetInstance()->GetKey('D'))
		{
			if (mPlayerState != PlayerState::roll) {
				mPlayerState = PlayerState::run;

				if (_mousePosition.x < playerPoint.x)
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
			}
			else {
				mAngle += 5;
				mSpeed = 5.f;
				if (mAngle >= 360) {
					mAngle = 0;
					mPlayerState = PlayerState::run;
				}
			}
			mX = mX + mSpeed;
			mCurrentAnimation->Play();
		}

		if (Input::GetInstance()->GetKeyUp('A') || Input::GetInstance()->GetKeyUp('D')) {
			if (mPlayerState != PlayerState::roll) {
				mPlayerState = PlayerState::idle;

				if (mCurrentAnimation == mLeftRunAni || mCurrentAnimation == mLeftWalkAni) mCurrentAnimation = mLeftIdleAni;
				else if (mCurrentAnimation == mRightRunAni || mCurrentAnimation == mRightWalkAni) mCurrentAnimation = mRightIdleAni;
			}
		}
		//공격모션
		if (Input::GetInstance()->GetKeyDown('F'))
		{
			mPlayerState = PlayerState::attack;

			if (_mousePosition.x < playerPoint.x)
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
		
		
	}
	else if (mPlayerState == PlayerState::attack) {
		if (mCurrentAnimation == mLeftAttack) {
			if (mCurrentAnimation->GetIsPlay() == false) {
				mImage = IMAGEMANAGER->FindImage(L"Player_walk");
				mPlayerState = PlayerState::idle;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftIdleAni;
				mCurrentAnimation->Play();

			}
		}
		else if (mCurrentAnimation == mRightAttack) {
			if (mCurrentAnimation->GetIsPlay() == false) {
				mImage = IMAGEMANAGER->FindImage(L"Player_walk");
				mCurrentAnimation->Stop();
				mCurrentAnimation = mRightIdleAni;
				mCurrentAnimation->Play();

				mPlayerState = PlayerState::idle;
			}
		}

		
	}
}