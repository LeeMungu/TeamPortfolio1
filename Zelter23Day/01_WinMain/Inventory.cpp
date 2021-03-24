#include "pch.h"
#include "Inventory.h"
#include "Image.h"
#include "Item.h"
Inventory::Inventory(const string & name) : UI(name)
{
}

void Inventory::Init()
{
	mX = -1000;
	mY = -1000;

	mBaseImage = IMAGEMANAGER->FindImage(L"Inventory_base");
	mIsOpened = false;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 5; j++) {
			mSlotList[i][j].x = mX + j * 60 + 170;
			mSlotList[i][j].y = mY + i * 70 + 250;
			mSlotList[i][j].slotImage = IMAGEMANAGER->FindImage(L"Inventory_slot");
			mSlotList[i][j].slotImage2 = IMAGEMANAGER->FindImage(L"QuickSlot_slotBase");
			mSlotList[i][j].rect = RectMake(mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
			mSlotList[i][j].isFill = false;
		}
	}
}

void Inventory::Release()
{
}

void Inventory::Update()
{
	//�ӽ÷� ��ġ �����ؼ� ���� �ݴ°�ó�� ����
	if (mIsOpened == false) { //�κ��丮 ���������� 
		if (Input::GetInstance()->GetKeyDown('I')) 
		{ //i ������
			mX = WINSIZEX / 2 - 30;
			mY = WINSIZEY - 255 * 2;
			mIsOpened = true;

			//bool isEnd = false;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 5; j++) {
					mSlotList[i][j].x = mX + j * 60 + 170;
					mSlotList[i][j].y = mY + i * 70 + 250;
					mSlotList[i][j].rect = RectMake(mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);

					
				}
			}

			vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

			for (int i = 0; i < items.size(); ++i) {
				if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
				{
					items[i]->SetX(items[i]->GetX() + 1610);
					items[i]->SetY(items[i]->GetY() + 1210);
				}
			}
		}
		
	
		
		
	}
	else { //�κ��丮 �������� ��
		//�������� �� ���� �þ�� �پ���....
		if (Input::GetInstance()->GetKeyDown('I')) {//iŰ ������
			mX = -1000;
			mY = -1000;
			mIsOpened = false;
	
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 5; j++) {
					mSlotList[i][j].x = mX + j * 60 + 170;
					mSlotList[i][j].y = mY + i * 70 + 250;
					mSlotList[i][j].rect = RectMake(mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
				}
			}

			vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

			for (int i = 0; i < items.size(); ++i) {
				if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
				{
					if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
					{
						items[i]->SetX(items[i]->GetX() - 1610);
						items[i]->SetY(items[i]->GetY() - 1210);
					}
				}
			}
		}
	}
	
}

void Inventory::Render(HDC hdc)
{
	if (mIsOpened == true) {
		mBaseImage->ScaleRender(hdc, mX, mY, 295 * 2, 255 * 2);

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 5; j++) {
				mSlotList[i][j].slotImage->ScaleRender(hdc, mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
				//RenderRect(hdc, mSlotList[i][j].rect);
				
				if (mSlotList[i][j].isFill == true) {
					mSlotList[i][j].slotImage2->ScaleRender(hdc, mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
				}
			}
		}
	}
}
