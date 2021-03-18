#include "pch.h"
#include "Item.h"
#include "Image.h"
#include "Camera.h"
Item::Item(wstring imageKey, float x, float y, ItemType type) {
	mKeyName = imageKey;
	mX = x;
	mY = y;
	mType = type;
}
void Item::Init()
{
	//keyName�� ���� �̹��� ������
	if (mKeyName == L"Revolver") mImage = IMAGEMANAGER->FindImage(L"Weapon_pistol");

	mSizeX = mImage->GetFrameWidth();
	mSizeX = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Item::Release()
{
}

void Item::Update()
{
	//�÷��̾� �浹 �� �κ��丮�� ����
}

void Item::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->
		Render(hdc, mImage, mRect.left, mRect.top);
}
