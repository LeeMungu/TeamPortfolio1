#include "pch.h"
#include "Item.h"
#include "Image.h"
#include "Camera.h"
#include "Inventory.h"
Item::Item(wstring imageKey, float x, float y, int count, ItemKind kind) {
	mKeyName = imageKey;
	mX = x;
	mY = y;
	mCount = count;
	mItemKind = kind;

}
Item::Item(wstring imageKey, string name, float x, float y, int count, ItemKind kind) : GameObject(name)
{
	mKeyName = imageKey;
	mX = x;
	mY = y;
	mCount = count;
	mItemKind = kind;
}
void Item::Init()
{
	mImage = IMAGEMANAGER->FindImage(mKeyName);
	mType = ItemManager::GetInstance()->SetItemType(mKeyName);

	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mNumImage = IMAGEMANAGER->FindImage(L"SW_num");

	mIsClicking = false;
	mPrePosition.x = mX;
	mPrePosition.y = mY;
}

void Item::Release() {
}

void Item::Update()
{/*
	Inventory* inventory = (Inventory*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Inventory");
	mIsOpened = inventory->GetOpened();
	BagSlot(*slotList)[2] = inventory->GetSlotList();
	if(mItemKind == ItemKind::inventory && mIsOpened == true)
	{
		if (mIsClicking == false)
		{
			if (PtInRect(&mRect, _mousePosition) == true && Input::GetInstance()->GetKeyDown(VK_LBUTTON))
			{
				mIsClicking = true;
			}
			else
			{
				mPrePosition.x = mX;
				mPrePosition.y = mY;
			}
		}
		else 
		{
			mX = _mousePosition.x;
			mY = _mousePosition.y;

			if (Input::GetInstance()->GetKeyUp(VK_LBUTTON && mIsClicking == true)) //왼쪽 버튼 땠을 때
			{


				bool isMoved = false;

				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 2; j++) {
						RECT rc;
						RECT slotRc = slotList[i][j].rect;
						if (IntersectRect(&rc, &mRect, &slotRc))
						{
							
							if (slotList[i][j].isFill == true)
							{
								//원래 자리로 돌아감(스왑해야함)
								mX = mPrePosition.x;
								mY = mPrePosition.y;
								mIsClicking = false;
								isMoved = true;
								slotList[i][j].isFill = true;
								break;
							}
							else if(slotList[i][j].isFill == false)
							{

								mX = slotList[i][j].x + 25;
								mY = slotList[i][j].y + 25;
								slotList[i][j].isFill = true;
								mIsClicking = false;
								isMoved = true;
								break;
							}
						}
					}
				}

				if (isMoved == false && mIsClicking == true) {
					//원래 자리로 돌아감
					mX = mPrePosition.x;
					mY = mPrePosition.y;
					mIsClicking = false;
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++) 
			{
				RECT rc;
				RECT slotRc = slotList[i][j].rect;
				if (IntersectRect(&rc, &mRect, &slotRc))
				{
					slotList[i][j].isFill = true;
				}
				else
				{
					slotList[i][j].isFill = false;
				}
			}
		}
	}*/
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Item::Render(HDC hdc)
{
	if (mItemKind == ItemKind::drop) { //땅에 떨어져있을 땐 카메라 랜더
		CameraManager::GetInstance()->GetMainCamera()->
			Render(hdc, mImage, mRect.left, mRect.top);
	}
	else { //인벤토리, 퀵슬롯은 그냥 랜더
		mImage->Render(hdc, mRect.left, mRect.top);

		mNumImage->ScaleFrameRender(hdc, mX , mY + 5, mCount / 10 % 10, 0, 10, 10);
		mNumImage->ScaleFrameRender(hdc, mX + 6, mY + 5, mCount % 10, 0, 10, 10);
	}

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect, Gizmo::Color::Blue2);
	}
}