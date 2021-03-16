#include "pch.h"
#include "Zombie01.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"
#include "Camera.h"
#include "PathFinder.h"
#include "scene1.h"

void Zombie01::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Zombie01");
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	mX =  300;
	mY =  300;
	mSizeX = mImage->GetFrameWidth()*2;
	mSizeY = mImage->GetFrameHeight()*2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mAngle = 0;

	mHp = 10;
	mSpeed = 1.f;
	mAttack = 1;
	mTargeting = false;
	mTakenDamege = false;
	mDelay = 1.f;

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
	mLeftAttack->SetIsLoop(true);
	mLeftAttack->SetFrameUpdateTime(0.2f);

	mRightAttack = new Animation;

	mRightAttack->InitFrameByEndStart(0, 4, 4, 4, true);
	mRightAttack->SetIsLoop(true);
	mRightAttack->SetFrameUpdateTime(0.2f);

	mCurrentAnimation = mLeftMove;
	mCurrentAnimation->Play();
	mTest = false;
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

	if (mDistance > 30)
	{
		MovetoPlayer();
	}
	else
	{
		Attack();
	}
	

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Zombie01::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top,
		mCurrentAnimation->GetNowFrameX(), mCurrentAnimation->GetNowFrameY(),mSizeX,mSizeY);

	
	//D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2, L"공격실행", 30);

	
	
	D2DRenderer::GetInstance()->RenderText(WINSIZEX / 2, WINSIZEY / 2, to_wstring(mDistance), 30);

}

void Zombie01::Patrol()
{
}

void Zombie01::SearchPlayer()
{
}

void Zombie01::Attack()
{
	
}

void Zombie01::MovetoPlayer()
{
	vector<Tile*> Path = PathFinder::GetInstance()->FindPath(mTileList, mX / TileSize, mY / TileSize, mPlayer->GetX() / TileSize, mPlayer->GetY() / TileSize);

	if (Path.size() != NULL)
	{
		mAngle = Math::GetAngle(Path[Path.size() - 1]->GetX(), Path[Path.size() - 1]->GetY(), mX, mY);
		mX -= cosf(mAngle) * mSpeed;
		mY -= -sinf(mAngle) * mSpeed;
	}
}
