#include "pch.h"
#include "Zombie01.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"
#include "Camera.h"
#include "PathFinder.h"
#include "scene1.h"
#include "Gizmo.h"

void Zombie01::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Zombie01");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	mX =  500;
	mY =  500;
	mSizeX = mImage->GetFrameWidth()*2;
	mSizeY = mImage->GetFrameHeight()*2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCollisionBox = RectMakeCenter(mX, mY, mSizeX / 2, mSizeY / 3);
	mAttackBox = RectMakeCenter(mX, mY,0, 0);
	mAngle = 0;

	mHp = 10;
	mSpeed = 1.f;
	mAttack = 1;
	mTargeting = false;
	mIsInvincible = false;
	mDelay = 0.5f;

	mLeftMove = new Animation;
	mLeftMove->InitFrameByStartEnd(0, 1, 4, 1, true);
	mLeftMove->SetIsLoop(true);
	mLeftMove->SetFrameUpdateTime(0.2f);

	mRightMove = new Animation;
	mRightMove->InitFrameByStartEnd(0, 2, 4, 2, true);
	mRightMove->SetIsLoop(true);
	mRightMove->SetFrameUpdateTime(0.2f);

	mDownMove = new Animation;
	mDownMove->InitFrameByStartEnd(0, 0, 4, 0, true);
	mDownMove->SetIsLoop(true);
	mDownMove->SetFrameUpdateTime(0.2f);

	mUpMove = new Animation;
	mUpMove->InitFrameByStartEnd(0, 3, 4, 3, true);
	mUpMove->SetIsLoop(true);
	mUpMove->SetFrameUpdateTime(0.2f);

	mLeftAttack = new Animation;
	mLeftAttack->InitFrameByStartEnd(0, 4, 4, 4, true);
	mLeftAttack->SetIsLoop(false);
	mLeftAttack->SetFrameUpdateTime(0.01f);

	mRightAttack = new Animation;
	mRightAttack->InitFrameByStartEnd(0, 5, 4, 5, true);
	mRightAttack->SetIsLoop(false);
	mRightAttack->SetFrameUpdateTime(0.01f);

	mCurrentAnimation = mLeftMove;
	mCurrentAnimation->Play();

	mZombistate = ZombieState::Patrol;
	mIsSwichPos = false;
	mIsAttackTrigger = false;
	mSwithtime = 0;
	mDelayTime = 0;
}

void Zombie01::Release()
{
	SafeDelete(mLeftMove);
	SafeDelete(mRightMove);
	SafeDelete(mDownMove);
	SafeDelete(mUpMove);
	SafeDelete(mLeftAttack);
	SafeDelete(mRightAttack);

}

void Zombie01::Update()
{
	
	mDistance = Math::GetDistance(mPlayer->GetX(), mPlayer->GetY(), mX, mY);

	if (mDistance < 150 && mTargeting==false)
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

	if (mZombistate != ZombieState::Attack) //좀비공격 렉트 초기화
	{
		mAttackBox = RectMakeCenter(0, 0, 0, 0);
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
	
	if (mIsInvincible == true)
	{
		mInvincibleCount += Time::GetInstance()->DeltaTime();
	}
	if (mInvincibleCount > 0.4f && mIsInvincible == true)
	{
		mIsInvincible = false;
		mInvincibleCount = 0.f;
	}



	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCollisionBox = RectMakeCenter(mX, mY, mSizeX / 2, mSizeY / 3);

	Knockback();
	mCurrentAnimation->Update();

	if (mHp <= 0)
	{
		mIsDestroy = true;
	}
}

void Zombie01::Render(HDC hdc)
{
	//그림자
	CameraManager::GetInstance()->GetMainCamera()
		->ShadowRender(hdc, mImage, mRect.left, mRect.top,
			mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(), mSizeX, mSizeY, 0.3f,
			Time::GetInstance()->GetSceneTime());
	//이미지
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top,
		mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(),mSizeX,mSizeY);

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect);
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mAttackBox);
	}
	
	D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2-100, to_wstring(mAngle), 30);
	//D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2-100, to_wstring(mDistance), 30);
	if (mZombistate == ZombieState::Patrol)
	{
		D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2, L"정찰", 30);
	}
	else if (mZombistate == ZombieState::Attack)
	{
		D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2, L"공격", 30);
	}
	else if (mZombistate == ZombieState::Chase)
	{
		D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2, L"추격", 30);
	}
	else if (mZombistate == ZombieState::Die)
	{
		D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2, L"주금", 30);
	}

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		vector<Tile*> Path = PathFinder::GetInstance()->FindPath(mTileList, mX / TileSize, mY / TileSize, mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize);
		for (int i = 0; i < Path.size(); ++i)
		{
			CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, (Path[i]->GetRect()), Gizmo::Color::Blue2);
		}
	}

}

void Zombie01::Patrol()
{
	//지금은 좌우로만.
	mSwithtime += Time::GetInstance()->DeltaTime();

	if (mSwithtime > 3.f && mIsSwichPos==false)
	{
		mSwithtime = 0;
		mIsSwichPos = true;
	}
	else if(mSwithtime >3.f && mIsSwichPos == true)
	{
		mSwithtime = 0;
		mIsSwichPos = false;
	}

	if (mIsSwichPos)
	{
		mCurrentAnimation = mRightMove;
		mCurrentAnimation->Play();
		mX += 1;
	}
	else
	{
		mCurrentAnimation = mLeftMove;
		mCurrentAnimation->Play();
		mX -= 1;
	}


}

void Zombie01::SearchPlayer()
{
	if (mDistance > 53)
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

void Zombie01::Attack()
{
	if (mDistance > 53)
	{
		mZombistate = ZombieState::Chase;
	}
	else
	{		
		mDelayTime += Time::GetInstance()->DeltaTime();

		if (mDelayTime >= mDelay && mIsAttackTrigger==false)
		{
			if (mPlayer->GetRect().right >= mRect.right)
			{
				mCurrentAnimation = mRightAttack;
				mCurrentAnimation->Play();

				mDelayTime = 0;
				mIsAttackTrigger = true;
			}
			else if (mPlayer->GetRect().left <= mRect.left)
			{
				mCurrentAnimation = mLeftAttack;
				mCurrentAnimation->Play();
				mDelayTime = 0;
				mIsAttackTrigger = true;
			}
			
		}

		if (mCurrentAnimation == mRightAttack && mCurrentAnimation->GetNowFrameX() > 1 && mCurrentAnimation->GetNowFrameX() < 4)
		{
			mAttackBox = RectMakeCenter(mCollisionBox.right, mY, mSizeX, mSizeY*1.1);
		}
		else if (mCurrentAnimation == mLeftAttack && mCurrentAnimation->GetNowFrameX() > 1 && mCurrentAnimation->GetNowFrameX() < 4)
		{
			mAttackBox = RectMakeCenter(mCollisionBox.left, mY, mSizeX, mSizeY*1.1);
		}
	}

	if (mDelayTime >= mDelay/2 && mIsAttackTrigger == true)
	{
		mCurrentAnimation->Stop();
		mDelayTime = 0;
		mIsAttackTrigger = false;
	}
}

void Zombie01::MovetoPlayer()
{
	vector<Tile*> Path = PathFinder::GetInstance()->FindPath(mTileList, mX / TileSize, mY / TileSize, mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize);

	if (Path.size() != NULL)
	{
		if (Path.size() > 2)
		{
			mAngle = Math::GetAngle(Path[2]->GetX(), Path[2]->GetY(), mX, mY);
		
		}
		mX -= cosf(mAngle) * mSpeed;
		mY -= -sinf(mAngle) * mSpeed;
	}
	if (mPlayer->GetRect().left > mRect.right)
	{
		mCurrentAnimation = mRightMove;
		mCurrentAnimation->Play();
	}
	else if (mPlayer->GetRect().left < mRect.left)
	{
		mCurrentAnimation = mLeftMove;
		mCurrentAnimation->Play();
	}
	else if (mPlayer->GetRect().top > mRect.bottom)
	{
		mCurrentAnimation = mDownMove;
		mCurrentAnimation->Play();
	}
	else if(mPlayer->GetRect().bottom<mRect.top)
	{
		mCurrentAnimation = mUpMove;
		mCurrentAnimation->Play();
	}
	
}


