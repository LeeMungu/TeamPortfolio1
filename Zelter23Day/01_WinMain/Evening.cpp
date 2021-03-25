#include "pch.h"
#include "Evening.h"
#include "Image.h"

void Evening::Init()
{
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = WINSIZEX;
	mSizeY = WINSIZEY;
	mRect = RectMakeCenter(mX,mY,mSizeX,mSizeY);

	mImage = ImageManager::GetInstance()->FindImage(L"EveningBackground");
}

void Evening::Release()
{

}

void Evening::Update()
{

}

void Evening::Render(HDC hdc)
{
	mImage->EveningBackgroundRender(0.4f);
}
