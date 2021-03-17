#include "pch.h"
#include "Zombie02.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"
#include "Camera.h"
#include "PathFinder.h"
#include "scene1.h"

void Zombie02::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Zombie02");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	mX = 800;
	mY = 500;
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCollisionBox = RectMakeCenter(mX, mY, mSizeX / 2, mSizeY / 3);
	mAngle = 0;

	mHp = 10;
	mSpeed = 1.f;
	mAttack = 1;
	mTargeting = false;
	mTakenDamege = false;
	mDelay = 1.f;

	mLeftMove = new Animation;
	mLeftMove->InitFrameByStartEnd(0, 1, 4, 1, false);
	mLeftMove->SetIsLoop(true);
	mLeftMove->SetFrameUpdateTime(0.2f);

	mRightMove = new Animation;
	mRightMove->InitFrameByStartEnd(0, 2, 4, 2, false);
	mRightMove->SetIsLoop(true);
	mRightMove->SetFrameUpdateTime(0.2f);

	mDownMove = new Animation;
	mDownMove->InitFrameByStartEnd(0, 0, 4, 0, false);
	mDownMove->SetIsLoop(true);
	mDownMove->SetFrameUpdateTime(0.2f);

	mUpMove = new Animation;
	mUpMove->InitFrameByStartEnd(0, 3, 4, 3, false);
	mUpMove->SetIsLoop(true);
	mUpMove->SetFrameUpdateTime(0.2f);

	mLeftAttack = new Animation;
	mLeftAttack->InitFrameByStartEnd(0, 4, 4, 4, false);
	mLeftAttack->SetIsLoop(true);
	mLeftAttack->SetFrameUpdateTime(0.1f);
	mLeftAttack->SetCallbackFunc([this](){
		mAttackRect = RectMakeCenter(mX - mSizeX/2, mY, mSizeX, mSizeY);
	});

	mRightAttack = new Animation;
	mRightAttack->InitFrameByStartEnd(0, 5, 4, 5, false);
	mRightAttack->SetIsLoop(true);
	mRightAttack->SetFrameUpdateTime(0.1f);
	mRightAttack->SetCallbackFunc([this]() {
		mAttackRect = RectMakeCenter(mX + mSizeX / 2, mY, mSizeX, mSizeY);
	});

	mCurrentAnimation = mLeftMove;
	mCurrentAnimation->Play();

	mZombistate = ZombieState::Patrol;
	mIsSwichPos = false;
	mIsAttackTrigger = false;
	mSwithtime = 0;
	mDelayTime = 0;
}

void Zombie02::Release()
{
	SafeDelete(mLeftMove);
	SafeDelete(mRightMove);
	SafeDelete(mDownMove);
	SafeDelete(mUpMove);
	SafeDelete(mLeftAttack);
	SafeDelete(mRightAttack);
}

void Zombie02::Update()
{
	mDistance = Math::GetDistance(mPlayer->GetX(), mPlayer->GetY(), mX, mY);
	if (mZombistate != ZombieState::Attack)
	{
		mAttackRect = {0,0,0,0};
	}


	if (mDistance < 150 && mTargeting == false)
	{
		mTargeting = true;
		mZombistate = ZombieState::Chase;
	}

	if (mZombistate == ZombieState::Patrol)
	{
		Patrol();
	}
	else if (mZombistate == ZombieState::Attack)
	{
		Attack();
	}

	if (mTargeting)
	{
		SearchPlayer();

		if (mDistance > 1000)
		{
			mZombistate = ZombieState::Patrol;
			mTargeting = false;
		}
	}

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCollisionBox = RectMakeCenter(mX, mY, mSizeX / 2, mSizeY / 3);
	mCurrentAnimation->Update();
}

void Zombie02::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top,
		mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY);

	if (Input::GetInstance()->GetKey(VK_LSHIFT))
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect);
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mAttackRect);
	}
}

void Zombie02::Patrol()
{
	//지금은 좌우로만.
	mSwithtime += Time::GetInstance()->DeltaTime();

	if (mSwithtime > 3.f && mIsSwichPos == false)
	{
		mSwithtime = 0;
		mIsSwichPos = true;
	}
	else if (mSwithtime > 3.f && mIsSwichPos == true)
	{
		mSwithtime = 0;
		mIsSwichPos = false;
	}

	if (mIsSwichPos)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightMove;
		mCurrentAnimation->Play();
		mX += 1;
	}
	else
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftMove;
		mCurrentAnimation->Play();
		mX -= 1;
	}
}

void Zombie02::SearchPlayer()
{
	if (mDistance > 80)
	{
		mSpeed = 2.f;
		MovetoPlayer();
	}
	else
	{
		mSpeed = 0;
		mZombistate = ZombieState::Attack;
	}
}

void Zombie02::Attack()
{
	if (mDistance > 80)
	{
		mZombistate = ZombieState::Chase;
	}
	else
	{

		mDelayTime += Time::GetInstance()->DeltaTime();

		if (mDelayTime >= mDelay && mIsAttackTrigger == false)
		{
			if (mPlayer->GetRect().left > mRect.right)
			{
				mCurrentAnimation = mRightAttack;
				mCurrentAnimation->Play();
				mDelayTime = 0;
				mIsAttackTrigger = true;
			}
			else if (mPlayer->GetRect().left < mRect.left)
			{
				mCurrentAnimation = mLeftAttack;
				mCurrentAnimation->Play();
				mDelayTime = 0;
				mIsAttackTrigger = true;
			}

		}
	}

	if (mDelayTime >= mDelay / 2 && mIsAttackTrigger == true)
	{
		mCurrentAnimation->Stop();
		mDelayTime = 0;
		mIsAttackTrigger = false;
	}
}

void Zombie02::MovetoPlayer()
{
	vector<Tile*> Path = PathFinder::GetInstance()->
		FindPath(mTileList, mX / TileSize, mY / TileSize, mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize);

	if (Path.size() != NULL)
	{
		mAngle = Math::GetAngle(Path[Path.size() - 1]->GetX(), Path[Path.size() - 1]->GetY(), mX, mY);
		mX -= cosf(mAngle) * mSpeed;
		mY -= -sinf(mAngle) * mSpeed;
	}
	if (mPlayer->GetRect().left > mRect.right)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mRightMove;
		mCurrentAnimation->Play();
	}
	else if (mPlayer->GetRect().left < mRect.left)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mLeftMove;
		mCurrentAnimation->Play();
	}
	else if (mPlayer->GetRect().top > mRect.bottom)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mDownMove;
		mCurrentAnimation->Play();
	}
	else if (mPlayer->GetRect().bottom < mRect.top)
	{
		mCurrentAnimation->Stop();
		mCurrentAnimation = mUpMove;
		mCurrentAnimation->Play();
	}
}
