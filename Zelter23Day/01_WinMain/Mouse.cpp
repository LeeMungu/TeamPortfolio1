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
	mObjectType = objectLayer;
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mX = _mousePosition.x;
	mY = _mousePosition.y ;
	if (mObjectType == ObjectLayer::InteractObject)
	{
		mSizeX = mImage->GetFrameWidth() * InteractObjectSize;
		mSizeY = mImage->GetFrameHeight() * InteractObjectSize;
	}
	else
	{
		mSizeX = mImage->GetFrameWidth();
		mSizeY = mImage->GetFrameHeight();
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
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
		mY = _mousePosition.y - mSizeY/2;
		if (mTileCountX * InteractObjectSize % 2 == 1)//X���� Ȧ�� Ÿ��
		{
			mX = _mousePosition.x + (mTileCountX * InteractObjectSize -1) / 2 * TileSize;
		}
		else if (mTileCountX * InteractObjectSize % 2 == 0)//X���� ¦�� Ÿ��
		{
			mX = _mousePosition.x + (mTileCountX * InteractObjectSize) / 2 * TileSize -TileSize/2;
		}
	}
	else if (mObjectType == ObjectLayer::NoninteractObject)
	{
		mX = _mousePosition.x;
		mY = _mousePosition.y;
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
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
			InteractObject* interactObject = new InteractObject(mImageKey, _mousePosition.x + cameraRc.left, mY + mSizeY / 2 + cameraRc.top, mHpMax, mTileCountX, mTileCountY);
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
		//�̰����� �Ͽ�¡ �����־��ٰ�
	}
	else if (mObjectType == ObjectLayer::InteractObject)
	{
		for (int y = 0; y < mTileCountY*InteractObjectSize; ++y)
		{
			for (int x = 0; x < mTileCountX * InteractObjectSize; ++x)
			{
				RECT rc = RectMakeCenter(_mousePosition.x + x * TileSize, mRect.bottom - y * TileSize, TileSize, TileSize);
				RenderRect(hdc, rc);
			}
		}
		mImage->ScaleFrameRender(hdc, mRect.left, mRect.top,0,0,mSizeX,mSizeY);
	}
	else if (mObjectType == ObjectLayer::NoninteractObject)
	{
		mImage->ScaleRender(hdc, mRect.left, mRect.top,mSizeX,mSizeY);
	}
}

