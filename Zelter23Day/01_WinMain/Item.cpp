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
	mIsSeleted = false;
	mPrePosition.x = mX;
	mPrePosition.y = mY;
}

void Item::Release() {
}

void Item::Update()
{
	if (mItemKind == ItemKind::quickSlot )
	{
		if (mIsSeleted == false)
		{
			mY = ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 25;
		}
		else 
		{
			mY = ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 5;
		}
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Item::Render(HDC hdc)
{
	if (mItemKind == ItemKind::drop) { //¶¥¿¡ ¶³¾îÁ®ÀÖÀ» ¶© Ä«¸Þ¶ó ·£´õ
		CameraManager::GetInstance()->GetMainCamera()->
			Render(hdc, mImage, mRect.left, mRect.top);
	}
	else { //ÀÎº¥Åä¸®, Äü½½·ÔÀº ±×³É ·£´õ
		mImage->Render(hdc, mRect.left, mRect.top);

		mNumImage->ScaleFrameRender(hdc, mX , mY + 5, mCount / 10 % 10, 0, 10, 10);
		mNumImage->ScaleFrameRender(hdc, mX + 6, mY + 5, mCount % 10, 0, 10, 10);
	}

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect, Gizmo::Color::Blue2);
	}
}