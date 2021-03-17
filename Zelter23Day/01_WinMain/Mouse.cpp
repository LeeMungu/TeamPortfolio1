#include "pch.h"
#include "Mouse.h"
#include "Image.h"
#include "Tile.h"
#include "HousingObject.h"
#include "InteractObject.h"
#include "NonInteractObject.h"
#include "Camera.h"


Mouse::Mouse(wstring imageKey, ObjectLayer objectLayer)
{
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mX = _mousePosition.x;
	mY = _mousePosition.y ;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mObjectType = objectLayer;
}

void Mouse::Init()
{
	//기존 마우스들 지워주기 초기화
	vector<GameObject*> tempMouses = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Mouse);
	if (tempMouses.size() != NULL)
	{
		for (int i = 0; i < tempMouses.size(); ++i)
		{
			tempMouses[i]->SetIsDestroy(true);
		}
	}
}

void Mouse::Release()
{
}

void Mouse::Update()
{
	RECT cameraRc = CameraManager::GetInstance()->GetMainCamera()->GetRect();
	if (mObjectType == ObjectLayer::HousingObject)
	{
		//이곳에서 하우징 생성넣어줄것
	}
	else if (mObjectType == ObjectLayer::InteractObject)
	{
		mX = _mousePosition.x;
		mY = _mousePosition.y - mSizeY/2;
	}
	else if (mObjectType == ObjectLayer::NoninteractObject)
	{
		mX = _mousePosition.x;
		mY = _mousePosition.y;
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		//책안에서 클릭하면 무효
		vector<GameObject*> tempBook = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ToolBook);
		if (tempBook.size() != NULL)
		{
			for (int i = 0; i < tempBook.size(); ++i)
			{
				RECT tempBookRect = tempBook[i]->GetRect();
				if (PtInRect(&tempBookRect, _mousePosition))
				{
					return;
				}
			}
		}
		//누르면 생성
		if (mObjectType == ObjectLayer::HousingObject)
		{
			//이곳에서 하우징 생성넣어줄것
		}
		else if (mObjectType == ObjectLayer::InteractObject)
		{
			InteractObject* interactObject = new InteractObject(mImageKey, mX + cameraRc.left, mY + mSizeY / 2 + cameraRc.top, mHpMax, mTileCountX, mTileCountY);
			interactObject->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::InteractObject, interactObject);
		}
		else if (mObjectType == ObjectLayer::NoninteractObject)
		{
			NonInteractObject* noninteractObject = new NonInteractObject(mImageKey, mX + cameraRc.left, mY + cameraRc.top);
			noninteractObject->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::NoninteractObject, noninteractObject);
		}
	}
}

void Mouse::Render(HDC hdc)
{
	if (mObjectType == ObjectLayer::HousingObject)
	{
		//이곳에서 하우징 생성넣어줄것
	}
	else if (mObjectType == ObjectLayer::InteractObject)
	{
		for (int y = 0; y < mTileCountY; ++y)
		{
			for (int x = 0; x < mTileCountX; ++x)
			{
				RECT rc = RectMakeCenter(mX + x * TileSize, mRect.bottom - y * TileSize, TileSize, TileSize);
				RenderRect(hdc, rc);
			}
		}
		mImage->FrameRender(hdc, mRect.left, mRect.top,0,0);
	}
	else if (mObjectType == ObjectLayer::NoninteractObject)
	{
		mImage->Render(hdc, mRect.left, mRect.top);
	}
}

