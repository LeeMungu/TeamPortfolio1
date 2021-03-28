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

//������ �̹��� key�� ���� type�� ��������
ItemType ItemManager::SetItemType(wstring key)
{
	if (!mItemImageList.empty()) {
		return mItemImageList.find(key)->second;
	}
}

//���ͷ�Ʈ ������Ʈ �̸��� ���� ������ �������� ��������
void ItemManager::randomItem(wstring objectKey, float x, float y)
{
	//�տ� �����ڷ� ������Ʈ ����
	wstring str = objectKey.substr(0,3);

	//������Ʈ�� ���� �������� ������ key�� �����ش�
	wstring key;
	wstring key2;
	wstring key3;

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
		key = L"Iron1";
	}
	else if (str == L"Clo") //����
	{ 
		key = L"WoodBrench1";
		key2 = L"ClothRag";
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
		key = L"Iron1";
		key2 = L"Can";
	}
	else if (str == L"Dol") //����
	{ 
		key = L"ClothPiece";
		key3 = L"Shotgun";
	}
	else if (str == L"Dus") //��������
	{ 
		key2 = L"Bottle";
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
		key2 = L"RawMeat";
	}
	else if (str == L"Roc")  //��
	{
		key = L"Stone1";
	}
	else if (str == L"She")  //����
	{
		key = L"WoodBrench1";
		key2 = L"Bandage";
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
			key2 = L"RawMeat";
		}
	}
	else if (str == L"Sig") //������
	{ 
		key = L"Iron1";
	}
	else if (str == L"Sof") //����
	{ 
		key = L"WoodBrench1";
		key2 = L"ClothRag";
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
					//�÷��̾�� ������ �浹 ó��
					if (IntersectRect(&rc, &mItemsRc, &playerRc))
					{
						//�κ��丮�� �־���
						PutInInventory(((Item*)mItems[i])->GetKeyName(), ((Item*)mItems[i])->GetCount());
						//������ ������
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

	if (mItemInventoryList.find(key) == mItemInventoryList.end()) { //ó�� ����
		//������ ����Ʈ ���� �� �κ��丮���� �ҷ��ͼ� ����, �����
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
	bool isOpened = mInventory->GetOpened();

	//�������� �������� �巡�� �� ����ؼ� �ű� �� ����
	
	if (isOpened == true) //�κ��丮 �������� ����
	{
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			for (int q = 0; q < mItems.size(); ++q)
			{
				RECT itemRc = mItems[q]->GetRect();
				if (PtInRect(&itemRc, _mousePosition) == true)
				{
					if (((Item*)mItems[q])->GetIsClicking() == false) //�巡�� �� �ƴ� ��
					{
						mSeletedItemIndex = q;
						((Item*)mItems[mSeletedItemIndex])->SetIsClicking(true);

						//�����Ѽ��� ��ġ�ε��� ����
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
			
			//�巡�� ���� ��
			if (Input::GetInstance()->GetKey(VK_LBUTTON))
			{
				mItems[mSeletedItemIndex]->SetX(_mousePosition.x);
				mItems[mSeletedItemIndex]->SetY(_mousePosition.y);
			}
			//�ڸ���ȯ
			if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
			{
				//�κ��丮�ȿ���
				if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory
					|| ((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
				{
					//���� ��ġ
					int j = (_mousePosition.y - mSlotList[0][0].y) / 70;
					int k = (_mousePosition.x - mSlotList[0][0].x) / 60;
					//������ ��ġ
					int indexQ = (_mousePosition.x - mQuickSlotList[0].x) / 63;
					
					RECT rc;
					RECT slotRc = mSlotList[j][k].rect;
					RECT itemRc = mItems[mSeletedItemIndex]->GetRect();
					RECT quickSlotRc = mQuickSlotList[indexQ].rect;

					//�κ��丮 ���Կ� ��������
					if (IntersectRect(&rc, &slotRc, &itemRc))
					{
						IntersectInventory(j, k);
					}
					//�����Կ� ��������
					else if (IntersectRect(&rc, &quickSlotRc, &itemRc))
					{
						IntersectQuickSlot(indexQ);
					}
					//�κ��丮�� ������ ���� ���� ������ ����ϸ�
					else 
					{
						RECT rc;
						RECT itemRc = mItems[mSeletedItemIndex]->GetRect();
						RECT inventoryRc = mInventory->GetRect();
						//�κ��丮 �ȿ� ������ ��
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
						//�κ��丮 �ۿ� ������ ��
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
		//�κ��丮 �ȿ� ������ ��
		if (IntersectRect(&rc, &itemRc, &inventoryRc))
		{
			mItems[i]->SetX(((Item*)mItems[i])->mPrePosition.x);
			mItems[i]->SetY(((Item*)mItems[i])->mPrePosition.y);
		}
		//�κ��丮 �ۿ� ������ ��
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

	//������ ��������
	if (mSlotList[j][k].isFill == true)
	{
		//����
		for (int l = 0; l < mItems.size(); ++l)
		{
			if (mSlotList[j][k].x + 27 == mItems[l]->GetX() &&
				mSlotList[j][k].y + 27 == mItems[l]->GetY() && l != mSeletedItemIndex)
			{
				//�巡�� ���� �������� �����Կ� �־�����
				if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
				{
					//������ �������� �����Կ� �� �� �ִ� Ÿ���� ���� ����
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

						//������ �������� ���������� ����
						((Item*)mItems[l])->SetKind(ItemKind::quickSlot);
						//����� �������� �κ��丮�� ����
						((Item*)mItems[mSeletedItemIndex])->SetKind(ItemKind::inventory);
						//����� �������� ������ ���� ���� false
						((Item*)mItems[mSeletedItemIndex])->SetIsSelected(false);
					}
					//���� �Ұ����� Ÿ���̸� ������ ���� ������ ��ġ�� �ǵ�����.
					else
					{
						mItems[mSeletedItemIndex]->SetX(mQuickSlotList[mIndex].x + 27);
						mItems[mSeletedItemIndex]->SetY(mQuickSlotList[mIndex].y + 27);
					}
				}
				//�巡�� ���� �������� �κ��丮�� �־�����
				else
				{
					//������ �������� ��ȣ�ۿ��� �� ���� Ÿ���� ���� ��ȯ���ش�
					if (((Item*)mItems[l])->GetType() == ItemType::drink
						|| ((Item*)mItems[l])->GetType() == ItemType::food
						|| ((Item*)mItems[l])->GetType() == ItemType::gun
						|| ((Item*)mItems[l])->GetType() == ItemType::weapon
						|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::heal)
					{
						mItems[mSeletedItemIndex]->SetX(mSlotList[j][k].x + 27);
						mItems[mSeletedItemIndex]->SetY(mSlotList[j][k].y + 27);
						//������ �������� �̵�������
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
	//������ �������
	else
	{
		mItems[mSeletedItemIndex]->SetX(mSlotList[j][k].x + 27);
		mItems[mSeletedItemIndex]->SetY(mSlotList[j][k].y + 27);

		mSlotList[j][k].isFill = true;
		//�������� ���� �����Կ� �־�����
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
	//��ȣ�ۿ�Ǵ� ������ Ÿ�Ը�
	if (((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::drink
		|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::food
		|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::gun
		|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::weapon
		|| ((Item*)mItems[mSeletedItemIndex])->GetType() == ItemType::heal)
	{
		mItems[mSeletedItemIndex]->SetX(mQuickSlotList[indexQ].x + 27);
		mItems[mSeletedItemIndex]->SetY(mQuickSlotList[indexQ].y + 27);
		
		//������ ��������
		if (mQuickSlotList[indexQ].isFill == true)
		{
			//����
			for (int l = 0; l < mItems.size(); ++l)
			{
				if (mQuickSlotList[l].x + 27 == mItems[l]->GetX() &&
					mQuickSlotList[l].y + 27 == mItems[l]->GetY() && l != mSeletedItemIndex)
				{
					//�巡�� ���� �������� �κ��丮�� �־�����
					if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory)
					{
						mItems[l]->SetX(mSlotList[mIndexY][mIndexX].x + 27);
						mItems[l]->SetY(mSlotList[mIndexY][mIndexX].y + 27);

						//������ �������� �κ��丮�� ����
						((Item*)mItems[l])->SetKind(ItemKind::inventory);
						
						//����� �������� ���������� ����
						((Item*)mItems[mSeletedItemIndex])->SetKind(ItemKind::quickSlot);

						//������ ���� ����
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
					//�巡�� ���� �������� �����Կ� �־�����
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
		//������ �������
		else
		{
			mQuickSlotList[indexQ].isFill = true;
			//�������� ���� �κ��丮�� �־�����
			if (((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::inventory)
			{
				((Item*)mItems[mSeletedItemIndex])->SetKind(ItemKind::quickSlot);
				mSlotList[mIndexY][mIndexX].isFill = false;
			}
			//�������� ���� �����Կ� �־�����
			else if(((Item*)mItems[mSeletedItemIndex])->GetItemKind() == ItemKind::quickSlot)
			{
				mQuickSlotList[mIndex].isFill = false;
			}

			//���õ��ִ� ������â�̸�
			if (mQuickSlot->GetSelectedSlot() == indexQ + 1)
			{
				((Item*)mItems[mSeletedItemIndex])->SetIsSelected(true);
			}
		}
	}
	//��ȣ�ۿ��� �ȵǴ� �������� ���� �ִ� ������ ���ư���
	else
	{
		mItems[mSeletedItemIndex]->SetX(mSlotList[mIndexY][mIndexX].x + 27);
		mItems[mSeletedItemIndex]->SetY(mSlotList[mIndexY][mIndexX].y + 27);
	}
}

//���� Ű ������
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

//��ư�� ������ �����Կ� �ִ� �����۵��� ��ġ�� ��������
void ItemManager::QuickSlotRePositioning(int num)
{
	
	for (int i = 0; i < mItems.size(); ++i)
	{
		
		if (((Item*)mItems[i])->GetItemKind() == ItemKind::quickSlot)
		{
			//������ ��ġ�� �ִ� ������
			if (mItems[i]->GetX() == mQuickSlot->GetX() + (num - 1) * 63 + 90 + 27)
			{
				//���õ��ִ� �����̸�
				if (((Item*)mItems[i])->GetIsSelected())
				{
					//������ �����ϰ� ������ ��ġ�� ������
					((Item*)mItems[i])->SetIsSelected(false);
					mItems[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 27);

					//������ ������ ���� ����
					mSelectedItem.count = ((Item*)mItems[i])->GetCount();
					mSelectedItem.quickType = ((Item*)mItems[i])->GetType();
					mSelectedItem.key = ((Item*)mItems[i])->GetKeyName();
				}
				//���þȵ��ִ� �����̸�
				else
				{
					//�����ϰ� ������ ��ġ�� �÷���
					((Item*)mItems[i])->SetIsSelected(true);
					mItems[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 7);

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
				((Item*)mItems[i])->SetIsSelected(false);
				mItems[i]->SetY(ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "QuickSlot")->GetY() + 27);
			}
		}
	}
	
}

//�������� 0�� ���ϰ� �Ǹ� �������κ��丮����Ʈ map ���� ��������
void ItemManager::ItemCountCheck(Item* item, int y, int x)
{
	if (mItemInventoryList[item->GetKeyName()] <= 0)
	{
		mSlotList[y][x].isFill = false;
		mItemInventoryList.erase(item->GetKeyName());
		item->SetIsDestroy(true);
	}
}

//�������� �ִ� �κ��丮�� �ε����� ��������
POINT ItemManager::GetInventoryIndex(Item* item)
{
	POINT p;
	
	bool isChecked = false;
	//�κ��丮 �������� �� ���� �ִ� �ε����� �����
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


