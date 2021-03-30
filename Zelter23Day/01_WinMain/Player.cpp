#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "Tile.h"
#include "MapToolScene.h"
#include "Weapon.h"
#include "Bomb.h"
#include "ShotGun.h"

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

	mUpRoll = new Animation();
	mUpRoll->InitFrameByStartEnd(0, 2, 6, 2, false);
	mUpRoll->SetIsLoop(false);
	mUpRoll->SetFrameUpdateTime(0.08f);

	mDownRoll = new Animation();
	mDownRoll->InitFrameByEndStart(6, 3, 0, 3, false);
	mDownRoll->SetIsLoop(false);
	mDownRoll->SetFrameUpdateTime(0.08f);


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

	mStartTime_hunger = Time::GetInstance()->GetSceneTime();
	mStartTime_thirst = Time::GetInstance()->GetSceneTime();
	mStartTime_stemina = Time::GetInstance()->GetSceneTime();
	mStartTime_hp = Time::GetInstance()->GetSceneTime();

	mEquipment = Equipment::normal;
	mSelectedItem = ItemManager::GetInstance()->GetSelectedItem();

	//Weapon* weapon = new Weapon("weapon", mX, mY, 0, 0);
	//weapon->SetPlayerPtr(this);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, weapon);
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
	SafeDelete(mDownRoll);
	SafeDelete(mUpRoll);
}

void Player::Update()
{
	//플레이어앵글, 마우스 포지션 받아서 방향전환
	float cameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	float cameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;
	mAngle = Math::GetAngle(mX, mY, _mousePosition.x + cameraX, _mousePosition.y + cameraY);

	if (mPlayerState != PlayerState::roll)
	{
		if (mAngle > 45.f / 180.f * PI && mAngle < 135.f / 180.f * PI)
		{
			if (mIsMousePosition == true)
			{
				mCurrentAnimation->Stop();
				EquipmentPlayerImage(1);
				mCurrentAnimation = mUpIdleAni;
				mCurrentAnimation->Play();
			}
		}
	}

	if (mPlayerState != PlayerState::roll)
	{
		if (mAngle > 135.f / 180.f * PI && mAngle < 225.f / 180.f * PI)
		{
			if (mIsMousePosition == true)
			{
				mCurrentAnimation->Stop();
				EquipmentPlayerImage(1);
				mCurrentAnimation = mLeftIdleAni;
				mCurrentAnimation->Play();
			}
		}
	}


	if (mPlayerState != PlayerState::roll)
	{
		if (mAngle > 225.f / 180.f * PI && mAngle < 315.f / 180.f * PI)
		{
			if (mIsMousePosition == true)
			{
				mCurrentAnimation->Stop();
				EquipmentPlayerImage(1);
				mCurrentAnimation = mDownIdleAni;
				mCurrentAnimation->Play();
			}
		}
	}

	if (mPlayerState != PlayerState::roll)
	{
		if (mAngle > 360.f - 45.f / 180.f * PI || mAngle < 45.f / 180.f * PI)
		{
			if (mIsMousePosition == true)
			{
				mCurrentAnimation->Stop();
				EquipmentPlayerImage(1);
				mCurrentAnimation = mRightIdleAni;
				mCurrentAnimation->Play();
			}
		}
	}

	

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

	//총들고 쏘는거
	if(mSelectedItem.quickType == ItemType::gun)
	{
		mEquipment = Equipment::gun;

		if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Weapon).size() != NULL)
		{
			Weapon* tempWeapon = (Weapon*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Weapon, "Shotgun");
			if (tempWeapon != nullptr) tempWeapon->SetIsDestroy(true);

			Weapon* tempWeapon2 = (Weapon*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Weapon, "Pistol");
			if (tempWeapon2 != nullptr) tempWeapon2->SetIsDestroy(true);
		}

		if (mSelectedItem.key == L"Shotgun")
		{
			Weapon* shotgun = new Weapon("Shotgun", mX, mY, 0, 0);
			shotgun->Init();
			shotgun->SetPlayerPtr(this);
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Weapon, shotgun);
		}
		else
		{
			Weapon* pistol = new Weapon("Pistol", mX, mY, 0, 0);
			pistol->Init();
			pistol->SetPlayerPtr(this);
			ObjectManager::GetInstance()->AddObject(ObjectLayer::Weapon, pistol);
		}
	}
	else
	{
		mEquipment = Equipment::normal;
		if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Weapon).size() != NULL)
		{
			Weapon* tempWeapon = (Weapon*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Weapon, "Shotgun");
			if(tempWeapon != nullptr) tempWeapon->SetIsDestroy(true);

			Weapon* tempWeapon2 = (Weapon*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Weapon, "Pistol");
			if (tempWeapon2 != nullptr) tempWeapon2->SetIsDestroy(true);
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
					mCurrentAnimation = mDownRoll;
					mCurrentAnimation->Play();
				}
				else {
					mCurrentAnimation = mUpRoll;
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
				mDashTime = 0;
			}
			if (Input::GetInstance()->GetKeyDown(VK_RBUTTON))
			{
				return;
			}

			if (Input::GetInstance()->GetKey('W'))
			{
				mIsMousePosition = false;
				if (mIsMousePosition == false)
				{
					if (mPlayerState != PlayerState::roll) {
						mPlayerState = PlayerState::run;

						if (_mousePosition.y > playerPoint.y)
						{
							EquipmentPlayerImage(0);
							mCurrentAnimation = mDownWalkAni;
							mSpeed = 5.f;
							mCurrentAnimation->Play();

						}
						else {
							EquipmentPlayerImage(1);
							mCurrentAnimation = mUpRunAni;
							mSpeed = 10.f;
							mCurrentAnimation->Play();

						}
					}
					mY -= deltaTime * mSpeed + mDash;
				}
			}

			else if (Input::GetInstance()->GetKey('S'))
			{
				mIsMousePosition = false;
				if (mIsMousePosition == false)
				{
					if (mPlayerState != PlayerState::roll) {
						mPlayerState = PlayerState::run;

						if (_mousePosition.y < playerPoint.y)
						{
							EquipmentPlayerImage(0);
							mCurrentAnimation = mUpWalkAni;
							mSpeed = 5.f;
							mCurrentAnimation->Play();

						}
						else {
							EquipmentPlayerImage(1);
							mCurrentAnimation = mDownRunAni;
							mSpeed = 10.f;
							mCurrentAnimation->Play();

						}
					}
					mY += deltaTime * mSpeed + mDash;
				}
			}

			if (Input::GetInstance()->GetKeyUp('W') || Input::GetInstance()->GetKeyUp('S')) {
				EquipmentPlayerImage(0);
				mPlayerState = PlayerState::idle;
				mIsMousePosition = true;
				if (mCurrentAnimation == mDownRunAni || mCurrentAnimation == mDownWalkAni) mCurrentAnimation = mDownIdleAni;
				else if (mCurrentAnimation == mUpRunAni || mCurrentAnimation == mUpWalkAni) mCurrentAnimation = mUpIdleAni;
			}

			//좌우이동
			if (Input::GetInstance()->GetKey('A'))
			{
				mIsMousePosition = false;
				if (mIsMousePosition == false)
				{
					if (mPlayerState != PlayerState::roll) {
						mPlayerState = PlayerState::run;

						if (_mousePosition.x > playerPoint.x)
						{
							EquipmentPlayerImage(0);
							mCurrentAnimation = mRightWalkAni;
							mSpeed = 5.f;
						}
						else {
							EquipmentPlayerImage(1);
							mCurrentAnimation = mLeftRunAni;
							mSpeed = 10.f;
						}
					}
					mX -= deltaTime * mSpeed + mDash;
					mCurrentAnimation->Play();
				}
			}
			else if (Input::GetInstance()->GetKey('D'))
			{
				mIsMousePosition = false;
				if (mIsMousePosition == false)
				{
					if (mPlayerState != PlayerState::roll) {
						mPlayerState = PlayerState::run;

						if (_mousePosition.x < playerPoint.x)
						{
							EquipmentPlayerImage(0);
							mCurrentAnimation = mLeftWalkAni;
							mSpeed = 5.f;
						}
						else {
							EquipmentPlayerImage(1);
							mCurrentAnimation = mRightRunAni;
							mSpeed = 10.f;
						}
					}
					mX += deltaTime * mSpeed + mDash;
					mCurrentAnimation->Play();
				}
			}

			if (Input::GetInstance()->GetKeyUp('A') || Input::GetInstance()->GetKeyUp('D')) {
				mIsMousePosition = true;
				if (mPlayerState != PlayerState::roll) {
					EquipmentPlayerImage(0);
					mPlayerState = PlayerState::idle;

					if (mCurrentAnimation == mLeftRunAni || mCurrentAnimation == mLeftWalkAni) mCurrentAnimation = mLeftIdleAni;
					else if (mCurrentAnimation == mRightRunAni || mCurrentAnimation == mRightWalkAni) mCurrentAnimation = mRightIdleAni;
				}
			}


		}
		if (mPlayerState != PlayerState::roll)
		{
			if (Input::GetInstance()->GetKey('W'))
			{
				mIsMousePosition = false;
				if (mIsMousePosition == false)
				{
					if (mPlayerState != PlayerState::roll) {
						mPlayerState = PlayerState::run;

						if (_mousePosition.y > playerPoint.y)
						{
							EquipmentPlayerImage(0);
							mCurrentAnimation = mDownWalkAni;
							mSpeed = 5.f;
							mCurrentAnimation->Play();

						}
						else {
							EquipmentPlayerImage(1);
							mCurrentAnimation = mUpRunAni;
							mSpeed = 10.f;
							mCurrentAnimation->Play();

						}
					}
					mY -= deltaTime * mSpeed + mDash;
				}
			}

			else if (Input::GetInstance()->GetKey('S'))
			{
				mIsMousePosition = false;
				if (mIsMousePosition == false)
				{
					if (mPlayerState != PlayerState::roll) {
						mPlayerState = PlayerState::run;

						if (_mousePosition.y < playerPoint.y)
						{
							EquipmentPlayerImage(0);
							mCurrentAnimation = mUpWalkAni;
							mSpeed = 5.f;
							mCurrentAnimation->Play();

						}
						else {
							EquipmentPlayerImage(1);
							mCurrentAnimation = mDownRunAni;
							mSpeed = 10.f;
							mCurrentAnimation->Play();

						}
					}
					mY += deltaTime * mSpeed + mDash;
				}
			}

			if (Input::GetInstance()->GetKeyUp('W') || Input::GetInstance()->GetKeyUp('S')) {
				EquipmentPlayerImage(0);
				mPlayerState = PlayerState::idle;
				mIsMousePosition = true;
				if (mCurrentAnimation == mDownRunAni || mCurrentAnimation == mDownWalkAni) mCurrentAnimation = mDownIdleAni;
				else if (mCurrentAnimation == mUpRunAni || mCurrentAnimation == mUpWalkAni) mCurrentAnimation = mUpIdleAni;
			}

			//좌우이동
			if (Input::GetInstance()->GetKey('A'))
			{
				mIsMousePosition = false;
				if (mIsMousePosition == false)
				{
					if (mPlayerState != PlayerState::roll) {
						mPlayerState = PlayerState::run;

						if (_mousePosition.x > playerPoint.x)
						{
							EquipmentPlayerImage(0);
							mCurrentAnimation = mRightWalkAni;
							mSpeed = 5.f;
						}
						else {
							EquipmentPlayerImage(1);
							mCurrentAnimation = mLeftRunAni;
							mSpeed = 10.f;
						}
					}
					mX -= deltaTime * mSpeed + mDash;
					mCurrentAnimation->Play();
				}
			}
			else if (Input::GetInstance()->GetKey('D'))
			{
				mIsMousePosition = false;
				if (mIsMousePosition == false)
				{
					if (mPlayerState != PlayerState::roll) {
						mPlayerState = PlayerState::run;

						if (_mousePosition.x < playerPoint.x)
						{
							EquipmentPlayerImage(0);
							mCurrentAnimation = mLeftWalkAni;
							mSpeed = 5.f;
						}
						else {
							EquipmentPlayerImage(1);
							mCurrentAnimation = mRightRunAni;
							mSpeed = 10.f;
						}
					}
					mX += deltaTime * mSpeed + mDash;
					mCurrentAnimation->Play();
				}
			}

			if (Input::GetInstance()->GetKeyUp('A') || Input::GetInstance()->GetKeyUp('D')) {
				mIsMousePosition = true;
				if (mPlayerState != PlayerState::roll) {
					EquipmentPlayerImage(0);
					mPlayerState = PlayerState::idle;

					if (mCurrentAnimation == mLeftRunAni || mCurrentAnimation == mLeftWalkAni) mCurrentAnimation = mLeftIdleAni;
					else if (mCurrentAnimation == mRightRunAni || mCurrentAnimation == mRightWalkAni) mCurrentAnimation = mRightIdleAni;
				}
			}
			//공격모션
			if (Input::GetInstance()->GetKeyDown('F'))
			{
				SoundPlayer::GetInstance()->Play(L"AxeWhip", 0.8f
					* SoundPlayer::GetInstance()->GetEffectVolume());

				mIsMousePosition = false;
				if (mIsMousePosition == false)
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
		}
	}
			//공격모션 끝나면
	else if (mPlayerState == PlayerState::attack) {
		if (mCurrentAnimation == mLeftAttack) {
			if (mCurrentAnimation->GetIsPlay() == false) {
				EquipmentPlayerImage(0);
				mPlayerState = PlayerState::idle;
				mCurrentAnimation->Stop();
				mCurrentAnimation = mLeftIdleAni;
				mCurrentAnimation->Play();
			}
		}
		else if (mCurrentAnimation == mRightAttack) {
			if (mCurrentAnimation->GetIsPlay() == false) {
				EquipmentPlayerImage(0);
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
		mX += cosf(mTakenAngle) * mKnockbackDistance * Time::GetInstance()->DeltaTime();
		mY -= sinf(mTakenAngle) * mKnockbackDistance * Time::GetInstance()->DeltaTime();
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
	mTakenAngle = angle;
	mKnockbackDistance = force;
}


void Player::PlayerState() {
	float sceneTime_hunger = Time::GetInstance()->GetSceneTime();
	float sceneTime_thirst = Time::GetInstance()->GetSceneTime();
	float sceneTime_stemina = Time::GetInstance()->GetSceneTime();
	float sceneTime_hp;

	//목마름 떨어지는거
	if (mThirst > 0) {
		if (sceneTime_thirst - mStartTime_thirst > 25) {
			mThirst -= 7;
			mStartTime_thirst = Time::GetInstance()->GetSceneTime();
		}
	}
	//목마름 0이면
	else {
		mThirst = 0;
		sceneTime_hp = Time::GetInstance()->GetSceneTime();

		if (sceneTime_hp - mStartTime_hp > 5) {
			mHP -= 4;
			mStartTime_hp = Time::GetInstance()->GetSceneTime();
		}
	}
	//배고픔 떨어지는거
	if (mHunger > 0) {
		if (sceneTime_hunger - mStartTime_hunger > 33) {
			mHunger -= 7;
			mStartTime_hunger = Time::GetInstance()->GetSceneTime();
		}
	}
	//배고픔 0이면
	else {
		mHunger = 0;
		sceneTime_hp = Time::GetInstance()->GetSceneTime();

		if (sceneTime_hp - mStartTime_hp > 5) {
			mHP -= 4;
			mStartTime_hp = Time::GetInstance()->GetSceneTime();
		}
	}
	//스테미나 떨어지는거
	if (mStemina > 0) {
		if (sceneTime_stemina - mStartTime_stemina > 45) {
			mStemina -= 7;
			mStartTime_stemina = Time::GetInstance()->GetSceneTime();
		}
	}
	//스테미나 0이면
	else {
		mStemina = 0;
		sceneTime_hp = Time::GetInstance()->GetSceneTime();

		if (sceneTime_hp - mStartTime_hp > 5) {
			mHP -= 4;
			mStartTime_hp = Time::GetInstance()->GetSceneTime();
		}
	}

	if(mHP < 0)
	{
		mHP = 0;
	}
}

void Player::WeaponUse(bool a)
{
	if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Bullet).size() != NULL)
	{
		Weapon* tempweapon = (Weapon*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "weapon");
		tempweapon->SetIsUse(a);
	}
	
}

void Player::EquipmentPlayerImage(int mode)
{
	if (mode == 0) //walk
	{
		if (mEquipment == Equipment::normal)
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_walk");
		}
		else
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_Gunwalk");
		}
	}
	else //run
	{
		if (mEquipment == Equipment::normal)
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_run");
		}
		else
		{
			mImage = IMAGEMANAGER->FindImage(L"Player_Gunrun");
		}
	}
}
