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
	mY = _mousePosition.y;
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
	mX = _mousePosition.x;
	mY = _mousePosition.y;
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

		if (mObjectType == ObjectLayer::HousingObject)
		{
			//이곳에서 하우징 생성넣어줄것
		}
		else if (mObjectType == ObjectLayer::InteractObject)
		{
			InteractObject* interactObject = new InteractObject(mImageKey, mX + cameraRc.left, mY + cameraRc.top, 10);
			interactObject->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::InteractObject, interactObject);
		}
		else if (mObjectType == ObjectLayer::NoninteractObject)
		{
			NonInteractObject* noninteractObject = new NonInteractObject(mImageKey, mX+cameraRc.left, mY+cameraRc.top);
			noninteractObject->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::NoninteractObject, noninteractObject);
		}
	}
}

void Mouse::Render(HDC hdc)
{
	mImage->Render(hdc, mRect.left, mRect.top);
}

