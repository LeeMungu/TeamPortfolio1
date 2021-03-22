#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Tile.h"
#include "MapToolScene.h"
#include "Weapon.h"

Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mSpeed = 3.f;
	mHP = 100;
	mThirst = 100;
	mHunger = 100;
	mStemina = 100;
}

void Player::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Player_run");
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mIsInvincible = false;
	mIsKnockback = false;
	mInvincibleCount = 0;
	mAttacked = Attacked::left;

	mIsMousePosition = false;

	mCollisionBox = RectMakeCenter(mX , mY , mSizeX / 2, mSizeY / 3);
	mAttackBox = RectMakeCenter(0, 0, 0, 0);

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

	//Roll Animation
	mLeftRoll = new Animation();
	mLeftRoll->InitFrameByStartEnd(0, 0, 6, 0, false);
	mLeftRoll->SetIsLoop(false);
	mLeftRoll->SetFrameUpdateTime(0.08f);

	mRightRoll = new Animation();
	mRightRoll->InitFrameByEndStart(6, 1, 0, 1, false);
	mRightRoll->SetIsLoop(false);
	mRightRoll->SetFrameUpdateTime(0.08f);

	//Idle Animation
	mUpIdleAni = new Animation();
	mUpIdleAni->InitFrameByStartEnd(0, 0, 0, 0, false);
	mUpIdleAni->SetIsLoop(true);
	mUpIdleAni->SetFrameUpdateTime(0.1f);

	mDownIdleAni = new Animation();
	mDownIdleAni->InitFrameByStartEnd(0, 1, 0, 1, false);
	mDownIdleAni->SetIsLoop(true);
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
	mDash = 0;
	mDashTime = 0;

	Weapon* weapon = new Weapon(mX,mY,0,0);
	weapon->SetPlayerPtr(this);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, weapon);

	mStartTime_hunger = Time::GetInstance()->GetSceneTime();
	mStartTime_thirst = Time::GetInstance()->GetSceneTime();
	mStartTime_stemina = Time::GetInstance()->GetSceneTime();
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

	SafeDelete(mLeftRoll);
	SafeDelete(mRightRoll);
}

void Player::Update()
{
	PlayerCtrl();
	PlayerState();
	AttackRectMake();

	mCurrentAnimation->Update();
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY/3);
	mCollisionBox = RectMakeCenter(mX , mY, mSizeX / 2, mSizeY / 3);
	Knockback();

	if (mDash > 0)
	{
		mDashTime += Time::GetInstance()->DeltaTime();

		if (mDashTime > 0.4f)
		{
			mDashTime = 0;
			mDash = 0;
		}
	}

	if (mIsInvincible == true) //플레이어 무적 확인 및 초기화
	{
		mInvincibleCount += Time::GetInstance()->DeltaTime();
		if (mInvincibleCount >= 0.7f)
		{
			mIsInvincible = false;
		}
	}
	if (mCurrentAnimation != mLeftAttack && mCurrentAnimation != mRightAttack)
	{
		mAttackBox = RectMakeCenter(0, 0, 0, 0);
	}

//플레이어앵글, 마우스 포지션 받아서 방향전환
	float cameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	float cameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;
	mAngle = Math::GetAngle(mX, mY, _mousePosition.x+cameraX, _mousePosition.y+cameraY);

	if (mAngle > 45.f / 180.f * PI && mAngle < 135.f / 180.f * PI)
	{
		mIsMousePosition = true;
		if (mIsMousePosition == true)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mUpIdleAni;
			mCurrentAnimation->Play();
		}
		if (Input::GetInstance()->GetKey('W'))
		{
			mCurrentAnimation->Stop();
			mIsMousePosition == false;
		}
	}

	if (mAngle > 135.f / 180.f * PI && mAngle < 225.f / 180.f * PI)
	{
		mIsMousePosition = true;
		if (mIsMousePosition == true)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mLeftIdleAni;
			mCurrentAnimation->Play();
		}
		if (Input::GetInstance()->GetKey('A'))
		{
			mCurrentAnimation->Stop();
			mIsMousePosition == false;
		}
	}
	
	if (mAngle > 225.f / 180.f * PI && mAngle < 315.f / 180.f * PI)
	{
		mIsMousePosition = true;
		if (mIsMousePosition == true)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mDownIdleAni;
			mCurrentAnimation->Play();
		}
		if (Input::GetInstance()->GetKey('S'))
		{
			mCurrentAnimation->Stop();
			mIsMousePosition == false;
		}
	}
	if (mAngle > 360.f - 45.f / 180.f * PI || mAngle < 45.f / 180.f * PI)
	{
		mIsMousePosition = true;
		if (mIsMousePosition == true)
		{
			mCurrentAnimation->Stop();
			mCurrentAnimation = mRightIdleAni;
			mCurrentAnimation->Play();
		}
		if (Input::GetInstance()->GetKey('D'))
		{
			mCurrentAnimation->Stop();
			mIsMousePosition == false;
		}
	}

}

void Player::Render(HDC hdc)
{
	//그림자
	CameraManager::GetInstance()->GetMainCamera()
		->ShadowRender(hdc, mImage, mRect.left, mRect.top - 50, 
			mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY, 0.3f,
			Time::GetInstance()->GetSceneTime());
	//이미지
	CameraManager::GetInstance()->GetMainCamera()->
		ScaleFrameRender(hdc, mImage, mRect.left, mRect.top-50, mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect);
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mCollisionBox);
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mAttackBox);
	}

}

void Player::PlayerCtrl() {
	//플리이어 포인트 위치
	POINT playerPoint = CameraManager::GetInstance()->GetMainCamera()->GetPoint(GetX(), GetY());
	float deltaTime = Time::GetInstance()->DeltaTime() * 15.f;

	if (mPlayerState != PlayerState::attack) 
	{
		//달리는 상태에서만 구르기
		if (mPlayerState == PlayerState::run) {
			if (Input::GetInstance()->GetKeyDown(VK_RBUTTON)) { 
				mPlayerState = PlayerState::roll;

				mImage = IMAGEMANAGER->FindImage(L"Player_roll");
				mSpeed = 10.f;
				mDash = 6.f;
				mCurrentAnimation->Stop();

				if (mCurrentAnimation == mLeftRunAni)
				{
					mCurrentAnimation = mLeftRoll;
					mCurrentAnimation->Play();
				}
				else if (mCurrentAnimation == mRightRunAni) {
					mCurrentAnimation = mRightRoll;
					mCurrentAnimation->Play();
				}
				else if (mCurrentAnimation == mDownRunAni) {
					mCurrentAnimation = mRightRoll;
					mCurrentAnimation->Play();
				}
				else {
					mCurrentAnimation = mLeftRoll;
					mCurrentAnimation->Play();
				}

			}
		}
		//roll 상태 끝나면 run으로 전환해줌
		if (mPlayerState == PlayerState::roll)
		{
			if (mCurrentAnimation->GetIsPlay() == false) {
				mPlayerState = PlayerState::run;
				mCurrentAnimation->Stop();
				mDash = 0;
			}
			if (Input::GetInstance()->GetKeyDown(VK_RBUTTON))
			{
				return;
			}
		}
		

		//위아래 이동

		if (mIsMousePosition == false)
		{
			if (Input::GetInstance()->GetKey('W'))
			{
				if (mPlayerState != PlayerState::roll) {
					mPlayerState = PlayerState::run;

					if (_mousePosition.y > playerPoint.y)
					{
						mImage = IMAGEMANAGER->FindImage(L"Player_walk");
						mCurrentAnimation = mDownWalkAni;
						mSpeed = 5.f;
						mCurrentAnimation->Play();

					}
					else {
						mImage = IMAGEMANAGER->FindImage(L"Player_run");
						mCurrentAnimation = mUpRunAni;
						mSpeed = 10.f;
						mCurrentAnimation->Play();

					}
				}
				mY -= deltaTime * mSpeed + mDash;
			}
			else if (Input::GetInstance()->GetKey('S'))
			{
				if (mPlayerState != PlayerState::roll) {
					mPlayerState = PlayerState::run;

					if (_mousePosition.y < playerPoint.y)
					{
						mImage = IMAGEMANAGER->FindImage(L"Player_walk");
						mCurrentAnimation = mUpWalkAni;
						mSpeed = 5.f;
						mCurrentAnimation->Play();

					}
					else {
						mImage = IMAGEMANAGER->FindImage(L"Player_run");
						mCurrentAnimation = mDownRunAni;
						mSpeed = 10.f;
						mCurrentAnimation->Play();

					}
				}
				mY += deltaTime * mSpeed + mDash;
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
						mSpeed = 5.f;
					}
					else {
						mImage = IMAGEMANAGER->FindImage(L"Player_run");
						mCurrentAnimation = mLeftRunAni;
						mSpeed = 10.f;
					}
				}
				mX -= deltaTime * mSpeed + mDash;
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
						mSpeed = 5.f;
					}
					else {
						mImage = IMAGEMANAGER->FindImage(L"Player_run");
						mCurrentAnimation = mRightRunAni;
						mSpeed = 10.f;
					}
				}
				mX += deltaTime * mSpeed + mDash;
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
		
	}//공격모션 끝나면
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

void Player::AttackRectMake()
{
	if (mCurrentAnimation == mLeftAttack && mCurrentAnimation->GetNowFrameX() > 5)
	{
		mAttackBox = RectMakeCenter(mRect.left, mY, mSizeX / 3, mSizeY);
	}
	if (mCurrentAnimation == mRightAttack && mCurrentAnimation->GetNowFrameX() > 5)
	{
		mAttackBox = RectMakeCenter(mRect.right, mY, mSizeX / 3, mSizeY);
	}
}

void Player::Knockback()
{
	if (mIsKnockback == true)
	{
		mX += cosf(mAngle) * mKnockbackDistance * Time::GetInstance()->DeltaTime();
		mY -= sinf(mAngle) * mKnockbackDistance * Time::GetInstance()->DeltaTime();
		mKnockbackDistance -= 1700.2f * Time::GetInstance()->DeltaTime();
		if (mKnockbackDistance <= 0)
		{
			mIsKnockback = false;
		}
	}
}


void Player::ExecuteKnockback(float angle, float force)
{
	mIsKnockback = true;
	mAngle = angle;
	mKnockbackDistance = force;
}


void Player::PlayerState() {
	float sceneTime_hunger = Time::GetInstance()->GetSceneTime();
	float sceneTime_thirst = Time::GetInstance()->GetSceneTime();
	float sceneTime_stemina = Time::GetInstance()->GetSceneTime();

	if (mThirst > 0) {
		if (sceneTime_thirst - mStartTime_thirst > 30) {
			mThirst -= 7;
			mStartTime_thirst = Time::GetInstance()->GetSceneTime();
		}
	}
	else {
		mThirst = 0;
	}

	if (mHunger > 0) {
		if (sceneTime_hunger - mStartTime_hunger > 35) {
			mHunger -= 7;
			mStartTime_hunger = Time::GetInstance()->GetSceneTime();
		}
	}
	else {
		mHunger = 0;
	}

	if (mStemina > 0) {
		if (sceneTime_stemina - mStartTime_stemina > 40) {
			mStemina -= 7;
			mStartTime_stemina = Time::GetInstance()->GetSceneTime();
		}
	}
	else {
		mStemina = 0;
	}
}