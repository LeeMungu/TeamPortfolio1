#include "pch.h"
#include "Mouse.h"
#include "Image.h"
#include "Tile.h"
#include "InteractObject.h"

Mouse::Mouse(wstring imageKey)
{
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mX = _mousePosition.x;
	mY = _mousePosition.y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Mouse::Init()
{
}

void Mouse::Release()
{
}

void Mouse::Update()
{
	mX = _mousePosition.x;
	mY = _mousePosition.y;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		InteractObject* interactObject = new InteractObject(mImageKey, mX, mY, 10);
		interactObject->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Object,interactObject);
	}
}

void Mouse::Render(HDC hdc)
{
	mImage->Render(hdc, mRect.left, mRect.top);
}

