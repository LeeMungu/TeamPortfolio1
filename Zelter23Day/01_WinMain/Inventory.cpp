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

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 2; j++) {
			mSlotList[i][j].x = mX + i * 60 + 170;
			mSlotList[i][j].y = mY + j * 60 + 250;
			mSlotList[i][j].slotImage = IMAGEMANAGER->FindImage(L"Inventory_slot");
			mSlotList[i][j].rect = RectMake(mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
		}
	}


	//mTestItem[0][0] = new Item(L"Revolver", mSlotList[0][0].x, mSlotList[0][0].y, ItemKind::inventory);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mTestItem[0][0]);
}

void Inventory::Release()
{
}

void Inventory::Update()
{
	//아이템 이미지 키값하고 개수를 가진 리스트 가져옴
	mItemList = ItemManager::GetInstance()->GetmItemInventoryList();
	map<wstring, int>::iterator iter = mItemList.begin();
	

	//임시로 위치 조정해서 열고 닫는것처럼 보임
	if (mIsOpened == false) {
		if (Input::GetInstance()->GetKeyDown('I')) {
			mX = WINSIZEX / 2 - 30;
			mY = WINSIZEY - 255 * 2;
			mIsOpened = true;

			bool isEnd = false;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					mSlotList[i][j].x = mX + i * 60 + 170;
					mSlotList[i][j].y = mY + j * 60 + 250;
					mSlotList[i][j].rect = RectMake(mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);

					
				}
			}

			int k = 0;
			int q = 0;
			for (iter; iter != mItemList.end(); iter++) {
				Item* item = new Item(iter->first, mSlotList[k][q].x + 20, mSlotList[k][q].y + 10,
					iter->second, ItemKind::inventory);
				item->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::InventoryItem, item);
				k++;
				if (k >= 5) {
					k = 0;
					q++;
				}
			}
		}
	}
	else {
		if (Input::GetInstance()->GetKeyDown('I')) {
			mX = -1000;
			mY = -1000;
			mIsOpened = false;

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					mSlotList[i][j].x = mX + i * 60 + 170;
					mSlotList[i][j].y = mY + j * 60 + 250;
					mSlotList[i][j].rect = RectMake(mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
				}
			}

			mItemList.clear();
			
			vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

			for (int i = 0; i < items.size(); ++i) {
					items[i]->SetIsDestroy(true);
			}

			//mTestItem[0][0]->SetX(mSlotList[0][0].x);
			//mTestItem[0][0]->SetY(mSlotList[0][0].y);
		}
	}
	
}

void Inventory::Render(HDC hdc)
{
	if (mIsOpened == true) {
		mBaseImage->ScaleRender(hdc, mX, mY, 295 * 2, 255 * 2);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				mSlotList[i][j].slotImage->ScaleRender(hdc, mSlotList[i][j].x, mSlotList[i][j].y, 55, 55);
			}
		}
	}
}
