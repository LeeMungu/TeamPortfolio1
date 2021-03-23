#include "pch.h"
#include "Tablet.h"
#include "Image.h"


Tablet::Tablet(const string& name) : UI(name)
{
}

void Tablet::Init()
{
	mX = -1000;
	mY = -1000;

	mBaseImage = IMAGEMANAGER->FindImage(L"Tablet_base");
	mIsOpened = false;


}

void Tablet::Release()
{
}

void Tablet::Update()
{
	if (mIsOpened == false)
	{
		if (Input::GetInstance()->GetKeyDown('T'))
		{
			mX = WINSIZEX / 2 - 300;
			mY = WINSIZEY / 2 - 300;
			mIsOpened = true;
		}
	}
	else if (Input::GetInstance()->GetKeyDown('T'))
	{
		mX = -1000;
		mY = -1000;
		mIsOpened = false;
	}
}

void Tablet::Render(HDC hdc)
{
	if (mIsOpened == true)
	{
		mBaseImage->ScaleRender(hdc, mX, mY, 450 * 2 , 281 * 2);
	}
}
