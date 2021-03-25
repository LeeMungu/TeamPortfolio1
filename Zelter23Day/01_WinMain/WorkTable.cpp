#include "pch.h"
#include "WorkTable.h"
#include "Image.h"
#include "Item.h"
#include "Button.h"

WorkTable::WorkTable(const string& name)
	:UI(name)
{
	
}

void WorkTable::Init()
{
	
	mX = WINSIZEX / 2 - 350;
	mY = WINSIZEY / 2 - 250;
	mWorkTable = IMAGEMANAGER->FindImage(L"WorkTable");
	mSizeX = mWorkTable->GetFrameWidth() * 2;
	mSizeY = mWorkTable->GetFrameHeight() * 2;

	mIsTableOpen = false;
	mIsOpenTrigger = false;
	mStartBtn = new Button(L"WorkTable_start_btn", mX + 550, mY + 330, 2, [this]() {});
	mTimeUpBtn = new Button(L"WorkTable_Timer_up", mX + 490, mY + 10 + 330, 2, [this]() {});
	mTimeDownBtn = new Button(L"WorkTable_Timer_down", mX + 490, mY - 10 + 330, 2, [this]() {});
	mMakeWoodBoard = new Button(L"나무판", mX, mY, 100, 100, [this]() {});
	mNumImage = IMAGEMANAGER->FindImage(L"SW_num");
	

}

void WorkTable::Release()
{
}

void WorkTable::Update()
{

	if (mIsTableOpen && mIsOpenTrigger==false)
	{
		vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

		if (items.size() != NULL)
		{
			for (int i = 0; i < items.size(); ++i) {
				if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
				{
					if (((Item*)items[i])->GetKeyName() == L"WoodBrench1")
					{
						//버튼이 뜨고 그걸 누르면 옆에 이내용이 떠야하고
						


						Item* workTableitem = new Item(((Item*)items[i])->GetKeyName(),"wood", mX + 450, mY + 250, ((Item*)items[i])->GetCount(), ((Item*)items[i])->GetItemKind());
						workTableitem->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::InventoryItem, workTableitem);
					}
					
				}
			}
		}
	

		mIsOpenTrigger = true;
	}

}

void WorkTable::Render(HDC hdc)
{
	if (mIsTableOpen == true)
	{
		mWorkTable->ScaleRender(hdc, mX, mY, mSizeX, mSizeY);
		mStartBtn->Render(hdc);
		mTimeUpBtn->Render(hdc);
		mTimeDownBtn->Render(hdc);
	}


	vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

	if (items.size() != NULL)
	{
		for (int i = 0; i < items.size(); ++i) {
			if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
			{
				if (((Item*)items[i])->GetKeyName() == L"WoodBrench1")
				{
					mMakeWoodBoard->Render(hdc);
				}
			}
		}
	}

}

void WorkTable::DeleteItem()
{
	vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

	if (items.size() != NULL)
	{
		Item* tempWorkItem = (Item*)ObjectManager::GetInstance()->FindObject(ObjectLayer::InventoryItem, "wood");
		tempWorkItem->SetIsDestroy(true);
	}
	
}
