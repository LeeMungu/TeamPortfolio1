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
	mMakingTotalCount = 0;
	mMakingCount = 0;
	mMakeCost = 0;
	mMakeCost2 = 0;
	mStartBtn = new Button(L"WorkTable_start_btn", mX + 550, mY + 330, 2, [this]() {
		MakingItem(mBtnKey);
		if (mMakingCount > 0)
		{
			DeleteItem();
		}
		});
	mTimeUpBtn = new Button(L"WorkTable_Timer_up", mX + 490, mY - 10 + 330, 2, [this]() {
		if (mMakingTotalCount > mMakingCount)
		{
			mMakingCount++;
		}
		DeleteItem();
		Worktemplet(mBtnKey);
		});
	mTimeDownBtn = new Button(L"WorkTable_Timer_down", mX + 490, mY + 10 + 330, 2, [this]() {
		if (mMakingCount > 0)
		{
			mMakingCount--;
		}
		DeleteItem();
		Worktemplet(mBtnKey);
		});
	mMakeWoodBoard = new Button(L"나무판", mX + 230, mY + 120, 80, 50, [this]() {mBtnKey = "WoodBoard"; DeleteItem(); Worktemplet(mBtnKey); });
	//vmMakeBonFire = new Button(L"모닥불", mX + 230, mY + 140, 80, 50, [this]() {mBtnKey = "BonFire", Worktemplet(mBtnKey); });
	mMakeBarrigate = new Button(L"바리게이트", mX + 230, mY + 160, 80, 50, [this]() {mBtnKey = "Barrigate"; DeleteItem(); Worktemplet(mBtnKey); });
	mNumImage = IMAGEMANAGER->FindImage(L"SW_num");

}

void WorkTable::Release()
{
	SafeDelete(mStartBtn);
	SafeDelete(mTimeUpBtn);
	SafeDelete(mTimeDownBtn);
	SafeDelete(mMakeWoodBoard);
	SafeDelete(mMakeBonFire);
	SafeDelete(mMakeBarrigate);
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
					if (((Item*)items[i])->GetKeyName() == L"WoodBoard" || ((Item*)items[i])->GetKeyName() == L"Iron1")
					{
						if (mMakeBarrigate != nullptr)
						{
							mMakeBarrigate->Render(hdc);
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

void WorkTable::Worktemplet(string btnkey)
{
	if (mIsMakingOpen == false)
	{
		vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);
		if (btnkey == "WoodBoard")//나무판
		{
			if (items.size() != NULL)
			{
				for (int i = 0; i < items.size(); ++i) {
					if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
					{
						if (((Item*)items[i])->GetKeyName() == L"WoodBrench1")
						{
							mIsMakingOpen = true;
							mMakeCost = 2;
							//재료아이템
							Item* workTableitem = new Item(((Item*)items[i])->GetKeyName(), "wood", mX + 450, mY + 250, ((Item*)items[i])->GetCount(), ((Item*)items[i])->GetItemKind());
							workTableitem->Init();
							ObjectManager::GetInstance()->AddObject(ObjectLayer::MakingItem, workTableitem);
							//재료아이템 

							//만들어질 아이템
							mMakingTotalCount = (int)((Item*)items[i])->GetCount() / mMakeCost;
							if (mMakeCost > ((Item*)items[i])->GetCount())
							{
								mMakingCount = 0;
							}
							Item* maikingborad = new Item(L"WoodBoard", "makeboard", mX + 450, mY + 150, mMakingCount, ItemKind::holding); //holding을 만들아이템 종류로 잠깐 쓸게
							maikingborad->Init();
							ObjectManager::GetInstance()->AddObject(ObjectLayer::MakingItem, maikingborad);
						}

					}
				}
			}
		}

		if (btnkey == "Barrigate")//바리게이트
		{
			
			if (items.size() != NULL)
			{
				for (int i = 0; i < items.size(); ++i)
				{
					if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
					{
						mIsMakingOpen = true;
						if (((Item*)items[i])->GetKeyName() == L"WoodBoard")
						{
							//재료아이템
							Item* workTableitem = new Item(((Item*)items[i])->GetKeyName(), "WoodBoard", mX + 450, mY + 250, ((Item*)items[i])->GetCount(), ((Item*)items[i])->GetItemKind());
							workTableitem->Init();
							ObjectManager::GetInstance()->AddObject(ObjectLayer::MakingItem, workTableitem);
							mMakeItemCount = ((Item*)items[i])->GetCount();
						}

						if (((Item*)items[i])->GetKeyName() == L"Iron1") // 템 있을때 없을때 구분해주기
						{
							//재료아이템
							Item* workTableitemlron = new Item(((Item*)items[i])->GetKeyName(), "Iron", mX + 480, mY + 250, ((Item*)items[i])->GetCount(), ((Item*)items[i])->GetItemKind());
							workTableitemlron->Init();
							ObjectManager::GetInstance()->AddObject(ObjectLayer::MakingItem, workTableitemlron);
							mMakeItemCount2 = ((Item*)items[i])->GetCount();
						}
					}
				}
			}

			//만들어질 아이템의 총 갯수 계산
			if (mMakeItemCount > 1 && mMakeItemCount2 > 0)
			{
				mMakingTotalCount = (int)(mMakeItemCount + mMakeItemCount2)/3;
			}
			if ((mMakeItemCount + mMakeItemCount2) < 3)
			{
				mMakingCount = 0;
			}


			//만들어질 아이템
			Item* makeBarrigate = new Item(L"Barrigate", "makeBarrigate", mX + 450, mY + 150, mMakingCount, ItemKind::holding); //holding을 만들아이템 종류로 잠깐 쓸게
			makeBarrigate->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::MakingItem, makeBarrigate);

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
	if (mTimeUpBtn != nullptr)
	{
		mTimeUpBtn->Update();
	}
	if (mTimeDownBtn != nullptr)
	{
		mTimeDownBtn->Update();
	}
	if (mMakeBarrigate != nullptr)
	{
		mMakeBarrigate->Update();
	}
}

void WorkTable::MakingItem(string btnkey)
{
	vector<GameObject*> makeItem = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::MakingItem);
	if (btnkey == "WoodBoard")//나무판
	{
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
										((Item*)items[i])->SetCountMinus(mMakingCount * mMakeCost);
										ItemManager::GetInstance()->SetmItemListCount(L"WoodBrench1", ((Item*)items[i])->GetCount());
										POINT p = ItemManager::GetInstance()->GetInventoryIndex((Item*)items[i]);
										ItemManager::GetInstance()->ItemCountCheck(((Item*)items[i]), p.x, p.y);

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
	if (btnkey == "Barrigate")//바리게이트
	{
		if (makeItem.size() != NULL)
		{
			for (int i = 0; i < makeItem.size(); i++)
			{
				if (((Item*)makeItem[i])->GetName() == "makeBarrigate")
				{
					if (mMakingCount > 0)
					{
						vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);
						if (items.size() != NULL)
						{
							for (int i = 0; i < items.size(); ++i)
							{
								if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
								{
									if (((Item*)items[i])->GetKeyName() == L"WoodBoard")
									{
										((Item*)items[i])->SetCountMinus(mMakingCount * 2);
										ItemManager::GetInstance()->SetmItemListCount(L"WoodBoard", ((Item*)items[i])->GetCount());
										POINT p = ItemManager::GetInstance()->GetInventoryIndex((Item*)items[i]);
										ItemManager::GetInstance()->ItemCountCheck(((Item*)items[i]), p.x, p.y);
									}
								}
								if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
								{
									if (((Item*)items[i])->GetKeyName() == L"Iron1")
									{
										((Item*)items[i])->SetCountMinus(mMakingCount * 1);
										ItemManager::GetInstance()->SetmItemListCount(L"Iron1", ((Item*)items[i])->GetCount());
										POINT p = ItemManager::GetInstance()->GetInventoryIndex((Item*)items[i]);
										ItemManager::GetInstance()->ItemCountCheck(((Item*)items[i]), p.x, p.y);
									}
								}
							}
						}

						ItemManager::GetInstance()->PutInInventory(L"Barrigate", mMakingCount);
					}
				}

			}
		}
	}
	
}
