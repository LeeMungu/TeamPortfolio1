#include "pch.h"
#include "ItemManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Inventory.h"
#include "QuickSlot.h"
ItemManager::ItemManager()
{
	mItemImageList.insert(make_pair(L"Blade", ItemType::weapon));
	mItemImageList.insert(make_pair(L"CrowBar", ItemType::weapon));
	mItemImageList.insert(make_pair(L"IronAxe", ItemType::weapon));
	mItemImageList.insert(make_pair(L"IronHammer", ItemType::weapon));
	mItemImageList.insert(make_pair(L"Pipe", ItemType::weapon));
	mItemImageList.insert(make_pair(L"StoneAxe", ItemType::weapon));
	mItemImageList.insert(make_pair(L"StoneHammer", ItemType::weapon));
	mItemImageList.insert(make_pair(L"Torch", ItemType::weapon));


	mItemImageList.insert(make_pair(L"Rifle", ItemType::gun));
	mItemImageList.insert(make_pair(L"Rifle2", ItemType::gun));
	mItemImageList.insert(make_pair(L"Shotgun", ItemType::gun));
	mItemImageList.insert(make_pair(L"CrossBow", ItemType::gun));
	mItemImageList.insert(make_pair(L"Revolver", ItemType::gun));


	mItemImageList.insert(make_pair(L"PistolBullet", ItemType::bullet));
	mItemImageList.insert(make_pair(L"ShotgunBullet", ItemType::bullet));
	mItemImageList.insert(make_pair(L"RifleBullet", ItemType::bullet));
	mItemImageList.insert(make_pair(L"Arrow", ItemType::bullet));
	mItemImageList.insert(make_pair(L"SMGBullet", ItemType::bullet));


	mItemImageList.insert(make_pair(L"Bandage", ItemType::heal));


	mItemImageList.insert(make_pair(L"GrilApple", ItemType::food));
	mItemImageList.insert(make_pair(L"GrilMeat1", ItemType::food));
	mItemImageList.insert(make_pair(L"GrilStickMeat", ItemType::food));
	mItemImageList.insert(make_pair(L"RawApple", ItemType::food));
	mItemImageList.insert(make_pair(L"RawMeat", ItemType::food));


	mItemImageList.insert(make_pair(L"BackPack", ItemType::equipment));
	mItemImageList.insert(make_pair(L"CrossBag", ItemType::equipment));
	mItemImageList.insert(make_pair(L"Hats1", ItemType::equipment));
	mItemImageList.insert(make_pair(L"Hats3", ItemType::equipment));
	mItemImageList.insert(make_pair(L"Cloth1", ItemType::equipment));
	mItemImageList.insert(make_pair(L"Pants1", ItemType::equipment));
	mItemImageList.insert(make_pair(L"Pants2", ItemType::equipment));
	mItemImageList.insert(make_pair(L"Uniform", ItemType::equipment));
	mItemImageList.insert(make_pair(L"WaistBag", ItemType::equipment));


	mItemImageList.insert(make_pair(L"Charcol1", ItemType::material));
	mItemImageList.insert(make_pair(L"ClothPiece", ItemType::material));
	mItemImageList.insert(make_pair(L"ClothRag", ItemType::material));
	mItemImageList.insert(make_pair(L"Cup", ItemType::material));
	mItemImageList.insert(make_pair(L"Iron1", ItemType::material));
	mItemImageList.insert(make_pair(L"Iron2", ItemType::material));
	mItemImageList.insert(make_pair(L"Steel", ItemType::material));
	mItemImageList.insert(make_pair(L"Stone1", ItemType::material));
	mItemImageList.insert(make_pair(L"WoodBrench1", ItemType::material));
	mItemImageList.insert(make_pair(L"WoodBoard", ItemType::material));


	mItemImageList.insert(make_pair(L"Barrigate", ItemType::structure));
	mItemImageList.insert(make_pair(L"Bed", ItemType::structure));
	mItemImageList.insert(make_pair(L"BonFire1", ItemType::structure));
	mItemImageList.insert(make_pair(L"Chair", ItemType::structure));
	mItemImageList.insert(make_pair(L"ClothWorkTable", ItemType::structure));
	mItemImageList.insert(make_pair(L"CookTable", ItemType::structure));
	mItemImageList.insert(make_pair(L"MetalWorkTable", ItemType::structure));
	mItemImageList.insert(make_pair(L"StandTorch", ItemType::structure));
	mItemImageList.insert(make_pair(L"StorageBox", ItemType::structure));
	mItemImageList.insert(make_pair(L"Tent", ItemType::structure));
	mItemImageList.insert(make_pair(L"WoodBrench1", ItemType::structure));
	mItemImageList.insert(make_pair(L"WoodWorkTable", ItemType::structure));


	mItemImageList.insert(make_pair(L"Bottle", ItemType::drink));
	mItemImageList.insert(make_pair(L"Can", ItemType::drink));


}
void ItemManager::Init()
{
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	mIndexX = 0;
	mIndexY = 0;
	mIndex = 0;
	mSelectedItem.count = NULL;
	mSelectedItem.quickType = ItemType::end;
	mSelectedItem.key = L"";
}

void ItemManager::Release()
{
}

void ItemManager::Update()
{
	PickUpItems();
	MoveItems();
	//ItemRePositioning();
}

void ItemManager::Render(HDC hdc)
{
}



ItemType ItemManager::SetItemType(wstring key)
{
	if (!mItemImageList.empty()) {
		return mItemImageList.find(key)->second;
	}
}

void ItemManager::randomItem(wstring objectKey, float x, float y)
{
	//앞에 세글자로 오브젝트 구분
	wstring str = objectKey.substr(0,3);

	//오브젝트에 따라 랜덤으로 아이템 key를 정해준다
	wstring key;
	wstring key2;

	if (str == L"Ben") //벤치 - 나뭇가지
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Bus") //버스
	{ 
		key = L"Iron1";
	}
	else if (str == L"Cab") //캐비넷
	{ 
		key = L"Iron1";
	}
	else if (str == L"Car") //자동차
	{ 
		key = L"Iron1";
	}
	else if (str == L"Cha") //의자
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Clo") //옷장
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Com") //컴퓨터
	{ 
		key = L"Iron1";
	}
	else if (str == L"Dea") //dead tree
	{ 
		key = L"Charcol1";
	}
	else if (str == L"Des") //책상
	{
		key = L"WoodBrench1";
	}
	else if (str == L"dis") //자판기
	{ 
		key = L"Can";
	}
	else if (str == L"Dol") //인형
	{ 
		key = L"ClothPiece";
	}
	else if (str == L"Dus") //쓰레기통
	{ 

	}
	else if (str == L"Fan") //선풍기
	{ 
		key = L"Iron1";
	}
	else if (str == L"Han") //세면대
	{ 

	}
	else if (str == L"Mot") //오토바이
	{ 
		key = L"Iron1";
	}
	else if (str == L"Pla")  //화분
	{
		key = L"WoodBrench1";
	}
	else if (str == L"Ref")  //냉장고
	{
		key = L"Iron1";
	}
	else if (str == L"Roc")  //돌
	{
		key = L"Stone1";
	}
	else if (str == L"She")  //선반
	{
		key = L"WoodBrench1";
	}
	else if (str == L"Sho") 
	{
		wstring str2 = objectKey.substr(3, 1);
		if (str2 == L"e")  //신발장
		{
			key = L"WoodBrench1";
		}
		else  //쇼케이스
		{
			key = L"Iron1";
		}
	}
	else if (str == L"Sig") //전광판
	{ 
		key = L"Iron1";
	}
	else if (str == L"Sof") //소파
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Suv") //suv 자동차
	{ 
		key = L"Iron1";
	}
	else if (str == L"Tab") //테이블
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Toi") //변기
	{ 

	}
	else if (str == L"Tre") //나무
	{ 
		wstring str2 = objectKey.substr(4, 1);
		if (str2 == L"2")  //사과나무
		{
			key = L"RawApple";
		}
		else  //나머지
		{
			key = L"WoodBrench1";
		}
		y += 100;
	}
	else if (str == L"Tru") //트럭
	{ 
		key = L"Iron1";
	}
	else if (str == L"Tv1") //tv
	{ 
		key = L"Iron1";
	}
	else if (str == L"Was") //세탁기
	{ 
		key = L"Iron1";
	}
	else if (str == L"Wat") //식수대
	{ 
		key = L"Iron1";
	}
	else if (str == L"Wor") //작업대
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Zom") //좀비
	{ 
		key = L"RawMeat";
	}
	//재료 개수 랜덤
	if (key != L"") 
	{
		int randCount = Random::GetInstance()->RandomInt(1, 4);

		for (int i = 0; i < randCount; i++) 
		{
			DropItems(key, x , y);
		}
	}
}

void ItemManager::DropItems(wstring key, float x, float y, int count)
{
	//아이템을 생성하고 드랍한다
	string itemStr;
	itemStr.assign(key.begin(), key.end());

	Item* item = new Item(key, itemStr, x, y, count, ItemKind::drop);
	item->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, item);
}

void ItemManager::PickUpItems()
{
	//아이템 줍기
	//아이템 리스트 받아옴
	if (mPlayer->GetPlayerState() != PlayerState::attack)
	{
		vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Item);

		if (items.size() != NULL)
		{
			for (int i = 0; i < items.size(); ++i)
			{
				RECT rc;
				RECT itemsRc = ((Item*)items[i])->GetRect();
				RECT playerRc = mPlayer->GetRect();

				if (((Item*)items[i])->GetIsPossiblePick() == true)
				{
					//플레이어와 아이템 충돌 처리
					if (IntersectRect(&rc, &itemsRc, &playerRc))
					{
						//인벤토리에 넣어줌
						PutInInventory(((Item*)items[i])->GetKeyName(), ((Item*)items[i])->GetCount());
						//아이템 지워줌
						items[i]->SetIsDestroy(true);
					}
				}
			}
		}
	}
}

void ItemManager::PutInInventory(wstring key, int count)
{
	Inventory* inventory = (Inventory*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Inventory");
	BagSlot (*slotList)[5] = inventory->GetSlotList();

	string itemStr;
	itemStr.assign(key.begin(), key.end());

	Item* item;

	if (mItemInventoryList.find(key) == mItemInventoryList.end()) { //처음 생성
		//아이템 리스트 생성 후 인벤토리에서 불러와서 생성, 사용함
		mItemInventoryList.insert(make_pair(key, count));

		
		for (int y = 0; y < 2; y++) {
			bool isFill = false;
			for (int x = 0; x < 5; x++) {
				if (slotList[y][x].isFill == false) {

					item = new Item(key, itemStr, slotList[y][x].x + 27, slotList[y][x].y + 27, mItemInventoryList[key], ItemKind::inventory);
					item->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::InventoryItem, item);
					slotList[y][x].isFill = true;
					isFill = true;
					break;
				}
			}
			if (isFill == true) break;
		}
	}
	else { //이미 있는 아이템은 count 증가
		int num = mItemInventoryList[key];
		if (num + count < 99) {
			mItemInventoryList[key] += count;
			num = mItemInventoryList[key];
		}

		item = (Item*)ObjectManager::GetInstance()->FindObject(ObjectLayer::InventoryItem, itemStr);

		item->SetCount(num);
	}
}

void ItemManager::MoveItems()
{
	Inventory* inventory = (Inventory*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Inventory");
	BagSlot(*slotList)[5] = inventory->GetSlotList();
	bool isOpened = inventory->GetOpened();

	QuickSlot* quickSlot = (QuickSlot*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot");
	Slot *quickSlotList = quickSlot->GetSlotList();
	vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

	//아이템을 슬롯으로 드로그 앤 드롭해서 옮길 수 있음
	
	if (isOpened == true) //인벤토리 열려있을 때만
	{
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			for (int q = 0; q < items.size(); ++q)
			{
				RECT itemRc = items[q]->GetRect();
				if (PtInRect(&itemRc, _mousePosition) == true)
				{
					if (((Item*)items[q])->GetIsClicking() == false) //드래그 중 아닐 때
					{
						mSeletedItemIndex = q;
						((Item*)items[mSeletedItemIndex])->SetIsClicking(true);

						//선택한순간 위치인덱스 저장
						if (((Item*)items[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory)
						{
							int j = (_mousePosition.y - slotList[0][0].y) / 70;
							int k = (_mousePosition.x - slotList[0][0].x) / 60;
							mIndexY = j;
							mIndexX = k;
						}
						else if (((Item*)items[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
						{
							for (int j = 0; j < 5; j++)
							{
								RECT rc;
								RECT slotRc = quickSlotList[j].rect;
								RECT itemRc = items[mSeletedItemIndex]->GetRect();

								if (IntersectRect(&rc, &slotRc, &itemRc)) {
									mIndex = j;
									break;
								}
							}
						}
					}
				}
			}
		}
		if (((Item*)items[mSeletedItemIndex])->GetIsClicking() == true)
		{
			
			//드래그 중일 때
			if (Input::GetInstance()->GetKey(VK_LBUTTON))
			{
				items[mSeletedItemIndex]->SetX(_mousePosition.x);
				items[mSeletedItemIndex]->SetY(_mousePosition.y);
				((Item*)items[mSeletedItemIndex])->SetIsSelected(false);
			}
			//자리교환
			if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
			{
				//인벤토리안에서
				if (((Item*)items[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory
					|| ((Item*)items[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
				{
					//슬롯 위치
					int j = (_mousePosition.y - slotList[0][0].y) / 70;
					int k = (_mousePosition.x - slotList[0][0].x) / 60;
					
					RECT rc;
					RECT slotRc = slotList[j][k].rect;
					RECT itemRc = items[mSeletedItemIndex]->GetRect();
					//특정위치에 놓았다.
					if (IntersectRect(&rc, &slotRc, &itemRc))
					{
						//슬롯이 차있으면
						if (slotList[j][k].isFill == true)
						{
							//스왑
							for (int l = 0; l < items.size(); ++l)
							{
								if (slotList[j][k].x + 27 == items[l]->GetX() &&
									slotList[j][k].y + 27 == items[l]->GetY() && l != mSeletedItemIndex)
								{
									items[l]->SetX(slotList[mIndexY][mIndexX].x + 27);
									items[l]->SetY(slotList[mIndexY][mIndexX].y + 27);
									if (((Item*)items[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
									{
										((Item*)items[l])->SetKind(ItemKind::quickSlot);
									}
									break;
								}
							}
						}

						//아이템이 비어있든 차있든 이동, 변화
						items[mSeletedItemIndex]->SetX(slotList[j][k].x + 27);
						items[mSeletedItemIndex]->SetY(slotList[j][k].y + 27);
						((Item*)items[mSeletedItemIndex])->SetIsClicking(false);
						//아이템이 원래 퀵슬롯에 있었으면
						if (((Item*)items[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
						{
							((Item*)items[mSeletedItemIndex])->SetKind(ItemKind::inventory);
						}
						((Item*)items[mSeletedItemIndex])->SetIsClicking(false);
					}
				}
			}
		}
	}
					/*



					
				}

				//인벤토리 슬롯 외의 곳에 아이템 드롭하면
				if (isMoved == false)
				{
					RECT rc;
					RECT itemRc = items[i]->GetRect();
					RECT inventoryRc = inventory->GetRect();
					//인벤토리 안에 놓았을 때
					if (IntersectRect(&rc, &itemRc, &inventoryRc))
					{
						items[i]->SetX(((Item*)items[i])->mPrePosition.x);
						items[i]->SetY(((Item*)items[i])->mPrePosition.y);
					}
					//인벤토리 밖에 놓았을 때
					else
					{
						string  str = items[i]->GetName();
						wstring wstr = L"";
						wstr.assign(str.begin(), str.end());

						DropItems(wstr, mPlayer->GetX(), mPlayer->GetY() + 15, mItemInventoryList[wstr]);

						if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
						{
							slotList[mIndexX][mIndexY].isFill = false;
						}
						else
						{
							quickSlotList[mIndex].isFill = false;
						}
						mItemInventoryList.erase(wstr);
						items[i]->SetIsDestroy(true);
					}
					((Item*)items[i])->SetIsClicking(false);
				}
			}
			}
		//items.size() for문 끝
		*/
	
}


void ItemManager::ItemRePositioning()
{

	if (Input::GetInstance()->GetKeyDown('1'))
	{
		QuickSlotRePositioning(1);
	}
	else if (Input::GetInstance()->GetKeyDown('2'))
	{
		QuickSlotRePositioning(2);
	}
	else if (Input::GetInstance()->GetKeyDown('3'))
	{
		QuickSlotRePositioning(3);
	}
	else if (Input::GetInstance()->GetKeyDown('4'))
	{
		QuickSlotRePositioning(4);
	}
	else if (Input::GetInstance()->GetKeyDown('5'))
	{
		QuickSlotRePositioning(5);
	}
}

void ItemManager::QuickSlotRePositioning(int num)
{
	QuickSlot* quickSlot = (QuickSlot*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot");
	Slot *quickSlotList = quickSlot->GetSlotList();
	vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

	for (int i = 0; i < items.size(); ++i)
	{
		
		if (((Item*)items[i])->GetItemKind() == ItemKind::quickSlot)
		{
			//선택한 위치에 있는 아이템
			if (items[i]->GetX() == quickSlot->GetX() + (num - 1) * 63 + 90 + 27)
			{
				//선택돼있던 슬롯이면
				if (((Item*)items[i])->GetIsSelected())
				{
					//선택을 해제하고 아이템 위치를 내려줌
					((Item*)items[i])->SetIsSelected(false);
					items[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 25);

					//셀렉된 아이템 정보 저장
					mSelectedItem.count = ((Item*)items[i])->GetCount();
					mSelectedItem.quickType = ((Item*)items[i])->GetType();
					mSelectedItem.key = ((Item*)items[i])->GetKeyName();
				}
				//선택안돼있던 슬롯이면
				else
				{
					//선택하고 아이템 위치를 올려줌
					((Item*)items[i])->SetIsSelected(true);
					items[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 5);

					//셀렉된 아이템 정보 초기화
					mSelectedItem.count = NULL;
					mSelectedItem.quickType = ItemType::end;
					mSelectedItem.key = L"";
				}
			}
			//나머지 위치에 있는 아이템들
			else
			{
				//아이템 위치 내림
				((Item*)items[i])->SetIsSelected(false);
				items[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 25);
			}
		}
	}
	
}

void ItemManager::ItemCountCheck(Item* item, int y, int x)
{
	Inventory* inventory = (Inventory*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Inventory");
	BagSlot(*slotList)[5] = inventory->GetSlotList();


	if (mItemInventoryList[item->GetKeyName()] <= 0)
	{
		slotList[y][x].isFill = false;
		mItemInventoryList.erase(item->GetKeyName());
		item->SetIsDestroy(true);
	}
}

POINT ItemManager::GetInventoryIndex(Item* item)
{
	Inventory* inventory = (Inventory*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Inventory");
	BagSlot(*slotList)[5] = inventory->GetSlotList();

	POINT p;
	
	
	bool isChecked = false;
	//인벤토리 아이템일 때 현재 있는 인덱스를 기억함
	if (item->GetItemKind() == ItemKind::inventory)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 5; k++)
			{

				RECT rc;
				RECT slotRc = slotList[j][k].rect;
				RECT itemRc = item->GetRect();

				if (IntersectRect(&rc, &slotRc, &itemRc)) {
					p.x = j;
					p.y = k;
					isChecked = true;
					break;
				}
			}
			if (isChecked == true) break;
		}
	}
	
		

	return p;
}
