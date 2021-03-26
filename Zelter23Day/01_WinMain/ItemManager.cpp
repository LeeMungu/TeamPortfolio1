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
	//�տ� �����ڷ� ������Ʈ ����
	wstring str = objectKey.substr(0,3);

	//������Ʈ�� ���� �������� ������ key�� �����ش�
	wstring key;
	wstring key2;

	if (str == L"Ben") //��ġ - ��������
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Bus") //����
	{ 
		key = L"Iron1";
	}
	else if (str == L"Cab") //ĳ���
	{ 
		key = L"Iron1";
	}
	else if (str == L"Car") //�ڵ���
	{ 
		key = L"Iron1";
	}
	else if (str == L"Cha") //����
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Clo") //����
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Com") //��ǻ��
	{ 
		key = L"Iron1";
	}
	else if (str == L"Dea") //dead tree
	{ 
		key = L"Charcol1";
	}
	else if (str == L"Des") //å��
	{
		key = L"WoodBrench1";
	}
	else if (str == L"dis") //���Ǳ�
	{ 
		key = L"Can";
	}
	else if (str == L"Dol") //����
	{ 
		key = L"ClothPiece";
	}
	else if (str == L"Dus") //��������
	{ 

	}
	else if (str == L"Fan") //��ǳ��
	{ 
		key = L"Iron1";
	}
	else if (str == L"Han") //�����
	{ 

	}
	else if (str == L"Mot") //�������
	{ 
		key = L"Iron1";
	}
	else if (str == L"Pla")  //ȭ��
	{
		key = L"WoodBrench1";
	}
	else if (str == L"Ref")  //�����
	{
		key = L"Iron1";
	}
	else if (str == L"Roc")  //��
	{
		key = L"Stone1";
	}
	else if (str == L"She")  //����
	{
		key = L"WoodBrench1";
	}
	else if (str == L"Sho") 
	{
		wstring str2 = objectKey.substr(3, 1);
		if (str2 == L"e")  //�Ź���
		{
			key = L"WoodBrench1";
		}
		else  //�����̽�
		{
			key = L"Iron1";
		}
	}
	else if (str == L"Sig") //������
	{ 
		key = L"Iron1";
	}
	else if (str == L"Sof") //����
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Suv") //suv �ڵ���
	{ 
		key = L"Iron1";
	}
	else if (str == L"Tab") //���̺�
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Toi") //����
	{ 

	}
	else if (str == L"Tre") //����
	{ 
		wstring str2 = objectKey.substr(4, 1);
		if (str2 == L"2")  //�������
		{
			key = L"RawApple";
		}
		else  //������
		{
			key = L"WoodBrench1";
		}
		y += 100;
	}
	else if (str == L"Tru") //Ʈ��
	{ 
		key = L"Iron1";
	}
	else if (str == L"Tv1") //tv
	{ 
		key = L"Iron1";
	}
	else if (str == L"Was") //��Ź��
	{ 
		key = L"Iron1";
	}
	else if (str == L"Wat") //�ļ���
	{ 
		key = L"Iron1";
	}
	else if (str == L"Wor") //�۾���
	{ 
		key = L"WoodBrench1";
	}
	else if (str == L"Zom") //����
	{ 
		key = L"RawMeat";
	}
	//��� ���� ����
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
	//�������� �����ϰ� ����Ѵ�
	string itemStr;
	itemStr.assign(key.begin(), key.end());

	Item* item = new Item(key, itemStr, x, y, count, ItemKind::drop);
	item->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Item, item);
}

void ItemManager::PickUpItems()
{
	//������ �ݱ�
	//������ ����Ʈ �޾ƿ�
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
					//�÷��̾�� ������ �浹 ó��
					if (IntersectRect(&rc, &itemsRc, &playerRc))
					{
						//�κ��丮�� �־���
						PutInInventory(((Item*)items[i])->GetKeyName(), ((Item*)items[i])->GetCount());
						//������ ������
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

	if (mItemInventoryList.find(key) == mItemInventoryList.end()) { //ó�� ����
		//������ ����Ʈ ���� �� �κ��丮���� �ҷ��ͼ� ����, �����
		mItemInventoryList.insert(make_pair(key, count));

		
		for (int y = 0; y < 2; y++) {
			bool isFill = false;
			for (int x = 0; x < 5; x++) {
				if (slotList[y][x].isFill == false) {

					item = new Item(key, itemStr, slotList[y][x].x + 25, slotList[y][x].y + 25, mItemInventoryList[key], ItemKind::inventory);
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
	else { //�̹� �ִ� �������� count ����
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
	//�������� �������� ��α� �� ����ؼ� �ű� �� ����

	if (isOpened == true) //�κ��丮 �������� ����
	{
		for (int i = 0; i < items.size(); ++i)
		{
			if (((Item*)items[i])->GetIsClicking() == false) //�巡�� �� �ƴ� ��
			{
				RECT itemRc = items[i]->GetRect();
				if (PtInRect(&itemRc, _mousePosition) == true && Input::GetInstance()->GetKeyDown(VK_LBUTTON))
				{
					bool isChecked = false;

					//�κ��丮 �������� �� ���� �ִ� �ε����� �����
					if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
					{
						for (int j = 0; j < 2; j++)
						{
							for (int k = 0; k < 5; k++)
							{

								RECT rc;
								RECT slotRc = slotList[j][k].rect;
								RECT itemRc = items[i]->GetRect();

								if (IntersectRect(&rc, &slotRc, &itemRc)) {
									mIndexX = j;
									mIndexY = k;
									isChecked = true;
									break;
								}
							}
							if (isChecked == true) break;
						}
					}
					//�� ���� �������� �� ���� �ִ� �ε����� �����
					else if(((Item*)items[i])->GetItemKind() == ItemKind::quickSlot)
					{
						for (int j = 0; j < 5; j++)
						{
							RECT rc;
							RECT slotRc = quickSlotList[j].rect;
							RECT itemRc = items[i]->GetRect();

							if (IntersectRect(&rc, &slotRc, &itemRc)) {
								mIndex = j;
								isChecked = true;
								break;
							}
						}
					}
					((Item*)items[i])->SetIsClicking(true);
				}
				else
				{
					((Item*)items[i])->mPrePosition.x = items[i]->GetX();
					((Item*)items[i])->mPrePosition.y = items[i]->GetY();

				}
			}
			else //�巡�� ���� ��
			{
				items[i]->SetX(_mousePosition.x);
				items[i]->SetY(_mousePosition.y);
				((Item*)items[i])->SetIsSelected(false);


				if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
				{
					bool isMoved = false;

					//�����۰� �κ��丮 ���� �浹 ó��
					if (((Item*)items[i])->GetItemKind() == ItemKind::inventory 
						|| ((Item*)items[i])->GetItemKind() == ItemKind::quickSlot) {
						for (int j = 0; j < 2; j++)
						{
							for (int k = 0; k < 5; k++)
							{
								RECT rc;
								RECT slotRc = slotList[j][k].rect;
								RECT itemRc = items[i]->GetRect();

								//����Ű�� �� ���� ���԰� �浹
								if (IntersectRect(&rc, &slotRc, &itemRc))
								{
									//������ ��������
									if (slotList[j][k].isFill == true)
									{
										//���߿� �����ϴ� �ɷ� ����
										items[i]->SetX(((Item*)items[i])->mPrePosition.x);
										items[i]->SetY(((Item*)items[i])->mPrePosition.y);
										((Item*)items[i])->SetIsClicking(false);
										isMoved = true;

										//�������� ���� �����Կ� �־�����
										if (((Item*)items[i])->GetItemKind() == ItemKind::quickSlot)
										{
											quickSlotList[mIndex].isFill = true;
										}
										//�������� ���� �κ��丮�� �־�����
										else
										{
											slotList[j][k].isFill = true;
											slotList[mIndexX][mIndexY].isFill = true;
										}

										break;
									}
									//������ ���������
									else if (slotList[j][k].isFill == false)
									{
										//�������� ��ġ�� ������ġ�� �������ְ� isFill true�� ����
										items[i]->SetX(slotList[j][k].x + 27);
										items[i]->SetY(slotList[j][k].y + 27);
										slotList[j][k].isFill = true;
										((Item*)items[i])->SetIsClicking(false);
										isMoved = true;

										//�������� ���� �����Կ� �־�����
										if (((Item*)items[i])->GetItemKind() == ItemKind::quickSlot)
										{
											quickSlotList[mIndex].isFill = false; //<-�̰� �ȵ� ���� �Ʊ� �ƴµ�?
											((Item*)items[i])->SetKind(ItemKind::inventory);
										}
										//�������� ���� �κ��丮�� �־�����
										else
										{

											//quickSlotList[mIndex].isFill = false;
											//�������� ���� �ִ� ������ isFill false�� ���ش�
											slotList[mIndexX][mIndexY].isFill = false;
										}
										break;
									}
								}

							}
						}
					
						// �����۰� ������ �浹 ó�� (�÷��̾� ��ȣ�ۿ� �ϴ°Ÿ� �ֱ�)
						if(((Item*)items[i])->GetType() == ItemType::drink || ((Item*)items[i])->GetType() == ItemType::food 
							|| ((Item*)items[i])->GetType() == ItemType::gun || ((Item*)items[i])->GetType() == ItemType::weapon)
						for (int j = 0; j < 5; j++)
						{
							RECT rc;
							RECT slotRc = quickSlotList[j].rect;
							RECT itemRc = items[i]->GetRect();
							//����Ű�� �� ���� ���԰� �浹
							if (IntersectRect(&rc, &slotRc, &itemRc))
							{
								//������ ��������
								if (quickSlotList[j].isFill == true)
								{
									//���߿� �����ϴ� �ɷ� ����
									items[i]->SetX(((Item*)items[i])->mPrePosition.x);
									items[i]->SetY(((Item*)items[i])->mPrePosition.y);
									((Item*)items[i])->SetIsClicking(false);
									isMoved = true;

									//�������� ���� �κ��丮�� �־�����
									if(((Item*)items[i])->GetItemKind() == ItemKind::inventory)
									{
										slotList[mIndexX][mIndexY].isFill = false;
									}
									//�������� ���� ���Կ� �־�����
									else
									{
										quickSlotList[mIndex].isFill = true;
									}
									break;
								}
								else {
									items[i]->SetX(quickSlotList[j].x + 27);
									items[i]->SetY(quickSlotList[j].y + 27);
									
									((Item*)items[i])->SetIsClicking(false);
									isMoved = true;
									//�������� ���� �κ��丮�� �־�����
									if (((Item*)items[i])->GetItemKind() == ItemKind::inventory)
									{
										slotList[mIndexX][mIndexY].isFill = false;
										((Item*)items[i])->SetKind(ItemKind::quickSlot);
										quickSlotList[j].isFill = true;
									}
									//�������� ���� ���Կ� �־�����
									else
									{
										quickSlotList[mIndex].isFill = false;
										quickSlotList[j].isFill = true;
									}
									break;
								}
							}
						}
					}

					//�κ��丮 ���� ���� ���� ������ ����ϸ�
					if (isMoved == false)
					{
						RECT rc;
						RECT itemRc = items[i]->GetRect();
						RECT inventoryRc = inventory->GetRect();
						//�κ��丮 �ȿ� ������ ��
						if (IntersectRect(&rc, &itemRc, &inventoryRc))
						{
							items[i]->SetX(((Item*)items[i])->mPrePosition.x);
							items[i]->SetY(((Item*)items[i])->mPrePosition.y);
						}
						//�κ��丮 �ۿ� ������ ��
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
			
		}//items.size() for�� ��
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
			//������ ��ġ�� �ִ� ������
			if (items[i]->GetX() == quickSlot->GetX() + (num - 1) * 63 + 90 + 27)
			{
				//���õ��ִ� �����̸�
				if (((Item*)items[i])->GetIsSelected())
				{
					//������ �����ϰ� ������ ��ġ�� ������
					((Item*)items[i])->SetIsSelected(false);
					items[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 25);

					//������ ������ ���� ����
					mSelectedItem.count = ((Item*)items[i])->GetCount();
					mSelectedItem.quickType = ((Item*)items[i])->GetType();
					mSelectedItem.key = ((Item*)items[i])->GetKeyName();
				}
				//���þȵ��ִ� �����̸�
				else
				{
					//�����ϰ� ������ ��ġ�� �÷���
					((Item*)items[i])->SetIsSelected(true);
					items[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 5);

					//������ ������ ���� �ʱ�ȭ
					mSelectedItem.count = NULL;
					mSelectedItem.quickType = ItemType::end;
					mSelectedItem.key = L"";
				}
			}
			//������ ��ġ�� �ִ� �����۵�
			else
			{
				//������ ��ġ ����
				((Item*)items[i])->SetIsSelected(false);
				items[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 25);
			}
		}
	}
	
}
