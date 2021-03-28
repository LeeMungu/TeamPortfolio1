#include "pch.h"
#include "ItemManager.h"
#include "GameObject.h"
#include "Player.h"

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
	mInventory = (Inventory*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Inventory");
	mSlotList = mInventory->GetSlotList();
	mQuickSlot = (QuickSlot*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot");
	mQuickSlotList = mQuickSlot->GetSlotList();
	mItems = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InventoryItem);

	PickUpItems();
	MoveItems();
	//CheckFillSlot();
	//ItemRePositioning();
}

void ItemManager::Render(HDC hdc)
{
}

//아이템 이미지 key에 따라 type을 지정해줌
ItemType ItemManager::SetItemType(wstring key)
{
	if (!mItemImageList.empty()) {
		return mItemImageList.find(key)->second;
	}
}

//인터렉트 오브젝트 이름에 따라 나오는 아이템을 지정해줌
void ItemManager::randomItem(wstring objectKey, float x, float y)
{
	//앞에 세글자로 오브젝트 구분
	wstring str = objectKey.substr(0,3);

	//오브젝트에 따라 랜덤으로 아이템 key를 정해준다
	wstring key;
	wstring key2;
	wstring key3;

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
		key = L"Iron1";
	}
	else if (str == L"Clo") //옷장
	{ 
		key = L"WoodBrench1";
		key2 = L"ClothRag";
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
		key = L"Iron1";
		key2 = L"Can";
	}
	else if (str == L"Dol") //인형
	{ 
		key = L"ClothPiece";
		key3 = L"Shotgun";
	}
	else if (str == L"Dus") //쓰레기통
	{ 
		key2 = L"Bottle";
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
		key2 = L"RawMeat";
	}
	else if (str == L"Roc")  //돌
	{
		key = L"Stone1";
	}
	else if (str == L"She")  //선반
	{
		key = L"WoodBrench1";
		key2 = L"Bandage";
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
			key2 = L"RawMeat";
		}
	}
	else if (str == L"Sig") //전광판
	{ 
		key = L"Iron1";
	}
	else if (str == L"Sof") //소파
	{ 
		key = L"WoodBrench1";
		key2 = L"ClothRag";
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
		int randCount = Random::GetInstance()->RandomInt(1, 3);

		for (int i = 0; i < randCount; i++) 
		{
			DropItems(key, x , y);
		}
	}
	if (key2 != L"")
	{
		int randCount = Random::GetInstance()->RandomInt(0, 2);

		for (int i = 0; i < randCount; i++)
		{
			DropItems(key2, x, y);
		}
	}
	if (key3 != L"")
	{
			DropItems(key3, x, y);
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
		vector<GameObject*> mItems = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Item);

		if (mItems.size() != NULL)
		{
			for (int i = 0; i < mItems.size(); ++i)
			{
				RECT rc;
				RECT mItemsRc = ((Item*)mItems[i])->GetRect();
				RECT playerRc = mPlayer->GetRect();

				if (((Item*)mItems[i])->GetIsPossiblePick() == true)
				{
					//플레이어와 아이템 충돌 처리
					if (IntersectRect(&rc, &mItemsRc, &playerRc))
					{
						//인벤토리에 넣어줌
						PutInInventory(((Item*)mItems[i])->GetKeyName(), ((Item*)mItems[i])->GetCount());
						//아이템 지워줌
						mItems[i]->SetIsDestroy(true);
					}
				}
			}
		}
	}
}

void ItemManager::PutInInventory(wstring key, int count)
{
	
	string itemStr;
	itemStr.assign(key.begin(), key.end());

	Item* item;

	if (mItemInventoryList.find(key) == mItemInventoryList.end()) { //처음 생성
		//아이템 리스트 생성 후 인벤토리에서 불러와서 생성, 사용함
		mItemInventoryList.insert(make_pair(key, count));

		
		for (int y = 0; y < 2; y++) {
			bool isFill = false;
			for (int x = 0; x < 5; x++) {
				if (mSlotList[y][x].isFill == false) {

					item = new Item(key, itemStr, mSlotList[y][x].x + 27, mSlotList[y][x].y + 27, mItemInventoryList[key], ItemKind::inventory);
					item->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::InventoryItem, item);
					mSlotList[y][x].isFill = true;
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
	bool isOpened = mInventory->GetOpened();

	//아이템을 슬롯으로 드래그 앤 드롭해서 옮길 수 있음
	
	if (isOpened == true) //인벤토리 열려있을 때만
	{
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			for (int q = 0; q < mItems.size(); ++q)
			{
				RECT itemRc = mItems[q]->GetRect();
				if (PtInRect(&itemRc, _mousePosition) == true)
				{
					if (((Item*)mItems[q])->GetIsClicking() == false) //드래그 중 아닐 때
					{
						mSeletedItemIndex = q;
						((Item*)mItems[mSeletedItemIndex])->SetIsClicking(true);

						//선택한순간 위치인덱스 저장
						if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory)
						{
							int j = (_mousePosition.y - mSlotList[0][0].y) / 70;
							int k = (_mousePosition.x - mSlotList[0][0].x) / 60;
							mIndexY = j;
							mIndexX = k;
						}
						else if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
						{
							mIndex = (_mousePosition.x - mQuickSlotList[0].x) / 63;
						}
					}
				}
			}
		}
		if (((Item*)mItems[mSeletedItemIndex])->GetIsClicking() == true)
		{
			
			//드래그 중일 때
			if (Input::GetInstance()->GetKey(VK_LBUTTON))
			{
				mItems[mSeletedItemIndex]->SetX(_mousePosition.x);
				mItems[mSeletedItemIndex]->SetY(_mousePosition.y);
			}
			//자리교환
			if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
			{
				//인벤토리안에서
				if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory
					|| ((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
				{
					//슬롯 위치
					int j = (_mousePosition.y - mSlotList[0][0].y) / 70;
					int k = (_mousePosition.x - mSlotList[0][0].x) / 60;
					//퀵슬롯 위치
					int indexQ = (_mousePosition.x - mQuickSlotList[0].x) / 63;
					
					RECT rc;
					RECT slotRc = mSlotList[j][k].rect;
					RECT itemRc = mItems[mSeletedItemIndex]->GetRect();
					RECT quickSlotRc = mQuickSlotList[indexQ].rect;

					//인벤토리 슬롯에 놓았으면
					if (IntersectRect(&rc, &slotRc, &itemRc))
					{
						IntersectInventory(j, k);
					}
					//퀵슬롯에 놓았으면
					else if (IntersectRect(&rc, &quickSlotRc, &itemRc))
					{
						IntersectQuickSlot(indexQ);
					}
					//인벤토리와 퀵슬롯 외의 곳에 아이템 드롭하면
					else 
					{
						RECT rc;
						RECT itemRc = mItems[mSeletedItemIndex]->GetRect();
						RECT inventoryRc = mInventory->GetRect();
						//인벤토리 안에 놓았을 때
						if (IntersectRect(&rc, &itemRc, &inventoryRc))
						{
							if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory)
							{
								mItems[mSeletedItemIndex]->SetX(mSlotList[mIndexY][mIndexX].x + 27);
								mItems[mSeletedItemIndex]->SetY(mSlotList[mIndexY][mIndexX].y + 27);
							}
							else if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
							{
								mItems[mSeletedItemIndex]->SetX(mQuickSlotList[mIndex].x + 27);
								mItems[mSeletedItemIndex]->SetY(mQuickSlotList[mIndex].y + 27);
							}
							((Item*)mItems[mSeletedItemIndex])->SetIsClicking(false);
						}
						//인벤토리 밖에 놓았을 때
						else
						{
							string  str = mItems[mSeletedItemIndex]->GetName();
							wstring wstr = L"";
							wstr.assign(str.begin(), str.end());

							DropItems(wstr, mPlayer->GetX(), mPlayer->GetY() + 15, mItemInventoryList[wstr]);

							if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory)
							{
								mSlotList[mIndexY][mIndexX].isFill = false;
							}
							else
							{
								mQuickSlotList[mIndex].isFill = false;
							}

							mItemInventoryList.erase(wstr);
							mItems[mSeletedItemIndex]->SetIsDestroy(true);

						}
						
					}
				}
			}
		}
	}
	
	
	/*

	
	if (isMoved == false)
	{
		RECT rc;
		RECT itemRc = mItems[i]->GetRect();
		RECT inventoryRc = inventory->GetRect();
		//인벤토리 안에 놓았을 때
		if (IntersectRect(&rc, &itemRc, &inventoryRc))
		{
			mItems[i]->SetX(((Item*)mItems[i])->mPrePosition.x);
			mItems[i]->SetY(((Item*)mItems[i])->mPrePosition.y);
		}
		//인벤토리 밖에 놓았을 때
		else
		{
			string  str = mItems[i]->GetName();
			wstring wstr = L"";
			wstr.assign(str.begin(), str.end());

			DropItems(wstr, mPlayer->GetX(), mPlayer->GetY() + 15, mItemInventoryList[wstr]);

			if (((Item*)mItems[i])->GetItemKind() == ItemKind::inventory)
			{
				mSlotList[mIndexX][mIndexY].isFill = false;
			}
			else
			{
				mQuickSlotList[mIndex].isFill = false;
			}
			mItemInventoryList.erase(wstr);
			mItems[i]->SetIsDestroy(true);
		}
		((Item*)mItems[i])->SetIsClicking(false);
	}
	*/
	
}

void ItemManager::IntersectInventory(int j, int k)
{
	((Item*)mItems[mSeletedItemIndex])->SetIsClicking(false);

	//슬롯이 차있으면
	if (mSlotList[j][k].isFill == true)
	{
		//스왑
		for (int l = 0; l < mItems.size(); ++l)
		{
			if (mSlotList[j][k].x + 27 == mItems[l]->GetX() &&
				mSlotList[j][k].y + 27 == mItems[l]->GetY() && l != mSeletedItemIndex)
			{
				//드래그 중인 아이템이 퀵슬롯에 있었으면
				if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
				{
					//스왑할 아이템이 퀵슬롯에 들어갈 수 있는 타입일 때만 스왑
					if (((Item*)mItems[l])->GetType() == ItemType::drink
						|| ((Item*)mItems[l])->GetType() == ItemType::food
						|| ((Item*)mItems[l])->GetType() == ItemType::gun
						|| ((Item*)mItems[l])->GetType() == ItemType::weapon
						|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::heal)
					{
						mItems[mSeletedItemIndex]->SetX(mSlotList[j][k].x + 27);
						mItems[mSeletedItemIndex]->SetY(mSlotList[j][k].y + 27);

						mItems[l]->SetX(mQuickSlotList[mIndex].x + 27);
						mItems[l]->SetY(mQuickSlotList[mIndex].y + 27);

						//스왑할 아이템을 퀵슬롯으로 설정
						((Item*)mItems[l])->SetKind(ItemKind::quickSlot);
						//드롭한 아이템을 인벤토리로 설정
						((Item*)mItems[mSeletedItemIndex])->SetKind(ItemKind::inventory);
						//드롭한 아이템의 퀵슬롯 선택 여부 false
						((Item*)mItems[mSeletedItemIndex])->SetIsSelected(false);
					}
					//스왑 불가능한 타입이면 아이템 원래 퀵슬롯 위치를 되돌린다.
					else
					{
						mItems[mSeletedItemIndex]->SetX(mQuickSlotList[mIndex].x + 27);
						mItems[mSeletedItemIndex]->SetY(mQuickSlotList[mIndex].y + 27);
					}
				}
				//드래그 중인 아이템이 인벤토리에 있었으면
				else
				{
					//스왑할 아이템이 상호작용할 수 있을 타입일 때만 교환해준다
					if (((Item*)mItems[l])->GetType() == ItemType::drink
						|| ((Item*)mItems[l])->GetType() == ItemType::food
						|| ((Item*)mItems[l])->GetType() == ItemType::gun
						|| ((Item*)mItems[l])->GetType() == ItemType::weapon
						|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::heal)
					{
						mItems[mSeletedItemIndex]->SetX(mSlotList[j][k].x + 27);
						mItems[mSeletedItemIndex]->SetY(mSlotList[j][k].y + 27);
						//스왑한 아이템을 이동시켜줌
						mItems[l]->SetX(mSlotList[mIndexY][mIndexX].x + 27);
						mItems[l]->SetY(mSlotList[mIndexY][mIndexX].y + 27);
					}
					else
					{
						mItems[mSeletedItemIndex]->SetX(mSlotList[mIndexY][mIndexX].x + 27);
						mItems[mSeletedItemIndex]->SetY(mSlotList[mIndexY][mIndexX].y + 27);
					}
				}
				break;
			}
		}
	}
	//슬롯이 비었으면
	else
	{
		mItems[mSeletedItemIndex]->SetX(mSlotList[j][k].x + 27);
		mItems[mSeletedItemIndex]->SetY(mSlotList[j][k].y + 27);

		mSlotList[j][k].isFill = true;
		//아이템이 원래 퀵슬롯에 있었으면
		if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
		{
			((Item*)mItems[mSeletedItemIndex])->SetKind(ItemKind::inventory);
			mQuickSlotList[mIndex].isFill = false;
		}
		else
		{
			mSlotList[mIndexY][mIndexX].isFill = false;
		}
	}
}

void ItemManager::IntersectQuickSlot(int indexQ)
{
	((Item*)mItems[mSeletedItemIndex])->SetIsClicking(false);
	//상호작용되는 아이템 타입만
	if (((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::drink
		|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::food
		|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::gun
		|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::weapon
		|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::heal)
	{
		mItems[mSeletedItemIndex]->SetX(mQuickSlotList[indexQ].x + 27);
		mItems[mSeletedItemIndex]->SetY(mQuickSlotList[indexQ].y + 27);
		
		//슬롯이 차있으면
		if (mQuickSlotList[indexQ].isFill == true)
		{
			//스왑
			for (int l = 0; l < mItems.size(); ++l)
			{
				if (mQuickSlotList[l].x + 27 == mItems[l]->GetX() &&
					mQuickSlotList[l].y + 27 == mItems[l]->GetY() && l != mSeletedItemIndex)
				{
					//드래그 중인 아이템이 인벤토리에 있었으면
					if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory)
					{
						mItems[l]->SetX(mSlotList[mIndexY][mIndexX].x + 27);
						mItems[l]->SetY(mSlotList[mIndexY][mIndexX].y + 27);

						//스왑할 아이템을 인벤토리로 설정
						((Item*)mItems[l])->SetKind(ItemKind::inventory);
						
						//드롭할 아이템을 퀵슬롯으로 설정
						((Item*)mItems[mSeletedItemIndex])->SetKind(ItemKind::quickSlot);

						//퀵슬롯 선택 여부
						if (((Item*)mItems[mSeletedItemIndex])->GetIsSelected() == true)
						{
							((Item*)mItems[mSeletedItemIndex])->SetIsSelected(false);
							((Item*)mItems[l])->SetIsSelected(true);
						}
						else if (((Item*)mItems[l])->GetIsSelected() == true)
						{
							((Item*)mItems[mSeletedItemIndex])->SetIsSelected(true);
							((Item*)mItems[l])->SetIsSelected(false);
						}
					}
					//드래그 중인 아이템이 퀵슬롯에 있었으면
					else
					{
						mItems[l]->SetX(mQuickSlotList[mIndex].x + 27);
						mItems[l]->SetY(mQuickSlotList[mIndex].y + 27);
						((Item*)mItems[l])->SetKind(ItemKind::quickSlot);
					}
					break;
				}
			}
		}
		//슬롯이 비었으면
		else
		{
			mQuickSlotList[indexQ].isFill = true;
			//아이템이 원래 인벤토리에 있었으면
			if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory)
			{
				((Item*)mItems[mSeletedItemIndex])->SetKind(ItemKind::quickSlot);
				mSlotList[mIndexY][mIndexX].isFill = false;
			}
			//아이템이 원래 퀵슬롯에 있었으면
			else if(((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
			{
				mQuickSlotList[mIndex].isFill = false;
			}

			//선택돼있는 퀵슬롯창이면
			if (mQuickSlot->GetSelectedSlot() == indexQ + 1)
			{
				((Item*)mItems[mSeletedItemIndex])->SetIsSelected(true);
			}
		}
	}
	//상호작용이 안되는 아이템은 원래 있던 곳으로 돌아간다
	else
	{
		mItems[mSeletedItemIndex]->SetX(mSlotList[mIndexY][mIndexX].x + 27);
		mItems[mSeletedItemIndex]->SetY(mSlotList[mIndexY][mIndexX].y + 27);
	}
}

//숫자 키 누르면
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

//버튼을 누르면 퀵슬롯에 있는 아이템들의 위치를 정렬해줌
void ItemManager::QuickSlotRePositioning(int num)
{
	
	for (int i = 0; i < mItems.size(); ++i)
	{
		
		if (((Item*)mItems[i])->GetItemKind() == ItemKind::quickSlot)
		{
			//선택한 위치에 있는 아이템
			if (mItems[i]->GetX() == mQuickSlot->GetX() + (num - 1) * 63 + 90 + 27)
			{
				//선택돼있던 슬롯이면
				if (((Item*)mItems[i])->GetIsSelected())
				{
					//선택을 해제하고 아이템 위치를 내려줌
					((Item*)mItems[i])->SetIsSelected(false);
					mItems[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 27);

					//셀렉된 아이템 정보 저장
					mSelectedItem.count = ((Item*)mItems[i])->GetCount();
					mSelectedItem.quickType = ((Item*)mItems[i])->GetType();
					mSelectedItem.key = ((Item*)mItems[i])->GetKeyName();
				}
				//선택안돼있던 슬롯이면
				else
				{
					//선택하고 아이템 위치를 올려줌
					((Item*)mItems[i])->SetIsSelected(true);
					mItems[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 7);

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
				((Item*)mItems[i])->SetIsSelected(false);
				mItems[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 27);
			}
		}
	}
	
}

//아이템이 0개 이하가 되면 아이템인벤토리리스트 map 에서 삭제해줌
void ItemManager::ItemCountCheck(Item* item, int y, int x)
{
	if (mItemInventoryList[item->GetKeyName()] <= 0)
	{
		mSlotList[y][x].isFill = false;
		mItemInventoryList.erase(item->GetKeyName());
		item->SetIsDestroy(true);
	}
}

//아이템이 있는 인벤토리의 인덱스를 리턴해줌
POINT ItemManager::GetInventoryIndex(Item* item)
{
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
				RECT slotRc = mSlotList[j][k].rect;
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


