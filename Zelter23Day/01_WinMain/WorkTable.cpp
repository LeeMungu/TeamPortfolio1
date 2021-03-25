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
						Item* workTableitem = new Item(((Item*)items[i])->GetKeyName(),"WoodBrench1", mX + 450, mY + 250, ((Item*)items[i])->GetCount(), ((Item*)items[i])->GetItemKind());
						workTableitem->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::InventoryItem, workTableitem);
					}
					
				}
			}
		}
	

		mIsOpenTrigger = true;
	}

	if (mIsTableOpen == false && mIsOpenTrigger == true)
	{
		vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);


		if (items.size() != NULL)
		{
			Item* tempWorkItem = (Item*)ObjectManager::GetInstance()->FindObject(ObjectLayer::InventoryItem, "WoodBrench1" );
			tempWorkItem->SetIsDestroy(true);	
		}

		
	
		mIsOpenTrigger = false;
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

}
