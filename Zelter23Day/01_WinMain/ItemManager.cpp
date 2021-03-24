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


	mItemImageList.insert(make_pair(L"GrilApple", ItemType::food));
	mItemImageList.insert(make_pair(L"GrilMeat1", ItemType::food));
	mItemImageList.insert(make_pair(L"GrilStickMeat", ItemType::food));
	mItemImageList.insert(make_pair(L"RawApple", ItemType::food));
	mItemImageList.insert(make_pair(L"Bandage", ItemType::food));
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
	indexX = 0;
	indexY = 0;
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
			DropItems(key, x - 50 + Random::GetInstance()->RandomInt(0, 100), 
				y - 50 + Random::GetInstance()->RandomInt(0, 100) );
		}
	}
}

void ItemManager::DropItems(wstring key, float x, float y)
{
	//아이템을 생성하고 드랍한다
	Item* item = new Item(key, x, y);
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

				//플레이어와 아이템 충돌 처리
				if (IntersectRect(&rc, &itemsRc, &playerRc))
				{
					//인벤토리에 넣어줌
					PutInInventory(((Item*)items[i])->GetKeyName());
					//아이템 지워줌
					items[i]->SetIsDestroy(true);
				}
			}
		}
	}
}

void ItemManager::PutInInventory(wstring key)
{
	Inventory* inventory = (Inventory*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Inventory");
	BagSlot (*slotList)[5] = inventory->GetSlotList();

	Item* item;

	if (mItemInventoryList.find(key) == mItemInventoryList.end()) { //처음 생성
		//아이템 리스트 생성 후 인벤토리에서 불러와서 생성, 사용함
		mItemInventoryList.insert(make_pair(key, 1));

		
		for (int y = 0; y < 2; y++) {
			bool isFill = false;
			for (int x = 0; x < 5; x++) {
				if (slotList[y][x].isFill == false) {
					string str;
					str.assign(key.begin(), key.end());
	
					item = new Item(key, str, slotList[y][x].x + 25, slotList[y][x].y + 25, mItemInventoryList[key], ItemKind::inventory);
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
		if (num < 99) {
			mItemInventoryList[key] = ++num;
		}

		string str;
		str.assign(key.begin(), key.end());
		item = (Item*)ObjectManager::GetInstance()->FindObject(str);
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
		

		for (int i = 0; i < items.size(); ++i)
		{
			if (((Item*)items[i])->GetIsClicking() == false) //드래그 중 아닐 때
			{
				RECT itemRc = items[i]->GetRect();
				if (PtInRect(&itemRc, _mousePosition) == true && Input::GetInstance()->GetKeyDown(VK_LBUTTON))
				{
					bool isChecked = false;
					for (int j = 0; j < 2; j++)
					{
						for (int k = 0; k < 5; k++)
						{

							RECT rc;
							RECT slotRc = slotList[j][k].rect;
							RECT itemRc = items[i]->GetRect();

							if (IntersectRect(&rc, &slotRc, &itemRc)) {
								indexX = j;
								indexY = k;
								isChecked = true;
								break;
							}
						}
						if (isChecked == true) break;
					}

					((Item*)items[i])->SetIsClicking(true);
				}
				else
				{
					((Item*)items[i])->mPrePosition.x = items[i]->GetX();
					((Item*)items[i])->mPrePosition.y = items[i]->GetY();

				}
			}
			else //드래그 중일 때
			{
				items[i]->SetX(_mousePosition.x);
				items[i]->SetY(_mousePosition.y);

				if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
				{
					bool isMoved = false;

					//아이템과 인벤토리 슬롯 충돌 처리
					if (((Item*)items[i])->GetItemKind() == ItemKind::inventory) {
						for (int j = 0; j < 2; j++)
						{
							for (int k = 0; k < 5; k++)
							{
								RECT rc;
								RECT slotRc = slotList[j][k].rect;
								RECT itemRc = items[i]->GetRect();

								//왼쪽키를 뗀 순간 슬롯과 충돌
								if (IntersectRect(&rc, &slotRc, &itemRc))
								{
									//슬롯이 차있으면
									if (slotList[j][k].isFill == true)
									{
										//나중에 스왑하는 걸로 수정
										items[i]->SetX(((Item*)items[i])->mPrePosition.x);
										items[i]->SetY(((Item*)items[i])->mPrePosition.y);
										((Item*)items[i])->SetIsClicking(false);
										isMoved = true;
										slotList[j][k].isFill = true;
										break;
									}
									//슬롯이 비어있으면
									else if (slotList[j][k].isFill == false)
									{
										//아이템의 위치를 슬롯위치로 지정해주고 isFill true로 해줌
										items[i]->SetX(slotList[j][k].x + 27);
										items[i]->SetY(slotList[j][k].y + 27);
										slotList[j][k].isFill = true;
										((Item*)items[i])->SetIsClicking(false);
										isMoved = true;

										//아이템이 원래 있던 슬롯은 isFill false를 해준다
										slotList[indexX][indexY].isFill = false;
										break;
									}
								}

							}
						}

						// 아이템과 퀵슬롯 충돌 처리 (플레이어 상호작용 하는거만 넣기)
						if(((Item*)items[i])->GetType() == ItemType::drink || ((Item*)items[i])->GetType() == ItemType::food 
							|| ((Item*)items[i])->GetType() == ItemType::gun || ((Item*)items[i])->GetType() == ItemType::weapon)
						for (int j = 0; j < 5; j++)
						{
							RECT rc;
							RECT slotRc = quickSlotList[j].rect;
							RECT itemRc = items[i]->GetRect();
							//왼쪽키를 뗀 순간 슬롯과 충돌
							if (IntersectRect(&rc, &slotRc, &itemRc))
							{
								//슬롯이 차있으면
								if (quickSlotList[j].isFill == true)
								{
									//나중에 스왑하는 걸로 수정
									items[i]->SetX(((Item*)items[i])->mPrePosition.x);
									items[i]->SetY(((Item*)items[i])->mPrePosition.y);
									((Item*)items[i])->SetIsClicking(false);
									isMoved = true;
									slotList[indexX][indexY].isFill = true;
									break;
								}
								else {
									items[i]->SetX(quickSlotList[j].x + 27);
									items[i]->SetY(quickSlotList[j].y + 27);
									((Item*)items[i])->SetKind(ItemKind::quickSlot);
									((Item*)items[i])->SetIsClicking(false);
									isMoved = true;
									slotList[indexX][indexY].isFill = false;

									//items[i]->SetIsDestroy(true);
									break;
								}
							}
						}
					}

					//인벤토리 슬롯 외의 곳에 아이템 드롭하면
					if (isMoved == false)
					{
						items[i]->SetX(((Item*)items[i])->mPrePosition.x);
						items[i]->SetY(((Item*)items[i])->mPrePosition.y);
						((Item*)items[i])->SetIsClicking(false);
					}

				}
				
			}
			
		}//items.size() for문 끝
	}
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
			if (items[i]->GetX() == quickSlot->GetX() + (num - 1) * 63 + 90 + 27)
			{
				
				if (((Item*)items[i])->GetIsSelected())
				{
					((Item*)items[i])->SetIsSelected(false);
				}
				else
				{
					((Item*)items[i])->SetIsSelected(true);
				}
			}
			else
			{
				((Item*)items[i])->SetIsSelected(false);
			}
		}
	}
	
}
