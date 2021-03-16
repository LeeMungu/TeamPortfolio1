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
	//���� ���콺�� �����ֱ� �ʱ�ȭ
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
		//�̰����� �Ͽ�¡ �����־��ٰ�
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
		if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mRect))//ī�޶� ���� �ȿ� ���� ��츸
		{
			//å�ȿ��� Ŭ���ϸ� ��ȿ
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
			//������ ����
			if (mObjectType == ObjectLayer::HousingObject)
			{
				//�̰����� �Ͽ�¡ �����־��ٰ�
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
}

void Mouse::Render(HDC hdc)
{
	if (mObjectType == ObjectLayer::HousingObject)
	{
		//�̰����� �Ͽ�¡ �����־��ٰ�
	}
	else if (mObjectType == ObjectLayer::InteractObject)
	{
		RECT rc = RectMakeCenter(mX, mRect.bottom, TileSize, TileSize);
		RenderRect(hdc, rc);
		mImage->Render(hdc, mRect.left, mRect.top);
	}
	else if (mObjectType == ObjectLayer::NoninteractObject)
	{
		mImage->Render(hdc, mRect.left, mRect.top);
	}
}

