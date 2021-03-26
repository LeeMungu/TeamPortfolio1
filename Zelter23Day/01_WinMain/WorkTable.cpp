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
	mIsMakingOpen = false;
	mStartBtn = new Button(L"WorkTable_start_btn", mX + 550, mY + 330, 2, [this]() {MakingItem(); });
	mTimeUpBtn = new Button(L"WorkTable_Timer_up", mX + 490, mY + 10 + 330, 2, [this]() {});
	mTimeDownBtn = new Button(L"WorkTable_Timer_down", mX + 490, mY - 10 + 330, 2, [this]() {});
	mMakeWoodBoard = new Button(L"나무판", mX + 230, mY + 120, 80, 50, [this]() {Worktemplet(); });
	mNumImage = IMAGEMANAGER->FindImage(L"SW_num");
	mMakingCount = 1;

}

void WorkTable::Release()
{
	SafeDelete(mStartBtn);

	SafeDelete(mTimeUpBtn);

	SafeDelete(mTimeDownBtn);

	SafeDelete(mMakeWoodBoard);
}

void WorkTable::Update()
{
	UpdateButton();
	if (mIsTableOpen && mIsOpenTrigger==false)
	{

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
	


		vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);
	
		if (items.size() != NULL)
		{
			for (int i = 0; i < items.size(); ++i) {
				if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
				{
					if (((Item*)items[i])->GetKeyName() == L"WoodBrench1")
					{
						if (mMakeWoodBoard != nullptr)
						{
							mMakeWoodBoard->Render(hdc);
						}
					}
				}
			}
		}
	}
}

void WorkTable::DeleteItem()
{
	mIsMakingOpen = false;
	vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);
	if (items.size() != NULL)
	{

		vector<GameObject*> makingItem = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::MakingItem);
		if (makingItem.size() != NULL)
		{
			for (int i = 0; i < makingItem.size(); i++)
			{
				makingItem[i]->SetIsDestroy(true);
			}
		}
	}
	
}

void WorkTable::Worktemplet()
{
	if (mIsMakingOpen == false)
	{
		vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

		if (items.size() != NULL)
		{
			for (int i = 0; i < items.size(); ++i) {
				if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
				{
					if (((Item*)items[i])->GetKeyName() == L"WoodBrench1")
					{
						mIsMakingOpen = true;
						//재료아이템
						Item* workTableitem = new Item(((Item*)items[i])->GetKeyName(), "wood", mX + 450, mY + 250, ((Item*)items[i])->GetCount(), ((Item*)items[i])->GetItemKind());
						workTableitem->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::MakingItem, workTableitem);
						//재료아이템 

						//만들어질 아이템
						mMakingCount = (int)((Item*)items[i])->GetCount() / 2;
						Item* maikingborad = new Item(L"WoodBoard", "makeboard", mX + 450, mY + 150, mMakingCount, ItemKind::holding); //holding을 만들아이템 종류로 잠깐 쓸게
						maikingborad->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::MakingItem, maikingborad);

						
					}

				}
			}
		}
	}
	
}

void WorkTable::UpdateButton()
{
	if (mMakeWoodBoard != nullptr)
	{
		mMakeWoodBoard->Update();
	}
	if (mStartBtn != nullptr)
	{
		mStartBtn->Update();
	}
}

void WorkTable::MakingItem()
{
	vector<GameObject*> makeItem = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::MakingItem);
	
	if (makeItem.size() != NULL)
	{
		for (int i = 0; i < makeItem.size(); i++)
		{
			if (((Item*)makeItem[i])->GetName() == "makeboard")
			{
				if (mMakingCount > 0)
				{
					vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);
					if (items.size() != NULL)
					{
						for (int i = 0; i < items.size(); ++i) {
							if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
							{
								if (((Item*)items[i])->GetKeyName() == L"WoodBrench1")
								{
									((Item*)items[i])->SetCountMinus(mMakingCount * 2);
									if (((Item*)items[i])->GetCount() <= 0)
									{
										((Item*)items[i])->SetIsDestroy(true);
									}
								}
							}
						}
					}

					ItemManager::GetInstance()->PutInInventory(L"WoodBoard", mMakingCount);
				}
			}
	
		}
	}
}
