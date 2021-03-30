#include "pch.h"
#include "BackGround.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"

BackGround::BackGround(const string& name, float x, float y)
	: GameObject(name)
{
	mX = x;
	mY = y;
	wstring temp;
	temp.assign(name.begin(), name.end());
	mImage = IMAGEMANAGER->FindImage(temp);

}

BackGround::BackGround(const string& name, float x, float y, wstring key)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mImage = IMAGEMANAGER->FindImage(key);

}

void BackGround::Init()
{
	//mSizeX = mImage->GetWidth();
	//mSizeY = mImage->GetHeight();
	//mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	//if (mName == "Background3")
	//{
	//	mAnimation = new Animation;
	//	mAnimation->InitFrameByStartEnd(0, 0, 2, 1, false);
	//	mAnimation->SetIsLoop(true);
	//	mAnimation->SetFrameUpdateTime(0.3f);
	//	mAnimation->Play();
	//}
}

void BackGround::Release()
{
}

void BackGround::Update()
{
	//if (mName == "Background3")
	//{
	//	mAnimation->Update();
	//}
}

void BackGround::Render(HDC hdc)
{
	//if (mName == "Background3")
	//{
	//	mImage->ScaleFrameRender(hdc, 0, 0,
	//		mAnimation->GetNowFrameX(),
	//		mAnimation->GetNowFrameY(),
	//		WINSIZEX, WINSIZEY);
	//}
	//else
	//{
	//	mImage->ScaleRender(hdc, 0, 0, WINSIZEX, WINSIZEY);
	//}
}
