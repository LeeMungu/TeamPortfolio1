#include "pch.h"
#include "ItemManager.h"
#include "GameObject.h"
#include "Player.h"
ItemManager::ItemManager()
{
	mItemImageList.insert(make_pair(L"Blade", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"CrowBar", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"IronAxe", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"IronHammer", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"Pipe", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"StoneAxe", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"StoneHammer", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"Torch", ItemType::Weapon));

	mItemImageList.insert(make_pair(L"Rifle", ItemType::Gun));
	mItemImageList.insert(make_pair(L"Rifle2", ItemType::Gun));
	mItemImageList.insert(make_pair(L"Shotgun", ItemType::Gun));
	mItemImageList.insert(make_pair(L"CrossBow", ItemType::Gun));
	mItemImageList.insert(make_pair(L"Revolver", ItemType::Gun));


	mItemImageList.insert(make_pair(L"PistolBullet", ItemType::Bullet));
	mItemImageList.insert(make_pair(L"ShotgunBullet", ItemType::Bullet));
	mItemImageList.insert(make_pair(L"RifleBullet", ItemType::Bullet));
	mItemImageList.insert(make_pair(L"Arrow", ItemType::Bullet));
	mItemImageList.insert(make_pair(L"SMGBullet", ItemType::Bullet));


	mItemImageList.insert(make_pair(L"GrilApple", ItemType::Food));
	mItemImageList.insert(make_pair(L"GrilMeat1", ItemType::Food));
	mItemImageList.insert(make_pair(L"GrilStickMeat", ItemType::Food));
	mItemImageList.insert(make_pair(L"RawApple", ItemType::Food));
	mItemImageList.insert(make_pair(L"RawMeat", ItemType::Food));

	mItemImageList.insert(make_pair(L"BackPack", ItemType::Equipment));
	mItemImageList.insert(make_pair(L"CrossBag", ItemType::Equipment));
	mItemImageList.insert(make_pair(L"Hats1", ItemType::Equipment));
	mItemImageList.insert(make_pair(L"Hats3", ItemType::Equipment));
	mItemImageList.insert(make_pair(L"Cloth1", ItemType::Equipment));
	mItemImageList.insert(make_pair(L"Pants1", ItemType::Equipment));
	mItemImageList.insert(make_pair(L"Pants2", ItemType::Equipment));
	mItemImageList.insert(make_pair(L"Uniform", ItemType::Equipment));
	mItemImageList.insert(make_pair(L"WaistBag", ItemType::Equipment));


	mItemImageList.insert(make_pair(L"Bandage", ItemType::Material));
	mItemImageList.insert(make_pair(L"Charcol1", ItemType::Material));
	mItemImageList.insert(make_pair(L"ClothPiece", ItemType::Material));
	mItemImageList.insert(make_pair(L"ClothRag", ItemType::Material));
	mItemImageList.insert(make_pair(L"Cup", ItemType::Material));
	mItemImageList.insert(make_pair(L"Iron1", ItemType::Material));
	mItemImageList.insert(make_pair(L"Iron2", ItemType::Material));
	mItemImageList.insert(make_pair(L"Steel", ItemType::Material));
	mItemImageList.insert(make_pair(L"Stone1", ItemType::Material));
	mItemImageList.insert(make_pair(L"WoodBrench1", ItemType::Material));
	mItemImageList.insert(make_pair(L"WoodBoard", ItemType::Material));


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


	mItemImageList.insert(make_pair(L"Bottle", ItemType::Drink));
	mItemImageList.insert(make_pair(L"Can", ItemType::Drink));


}
void ItemManager::Init()
{
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
}

void ItemManager::Release()
{
}

void ItemManager::Update()
{
	PickUpItems();
}

void ItemManager::Render(HDC hdc)
{
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
		key = L"Iron1";
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
			DropItems(key, x - 50 + Random::GetInstance()->RandomInt(0, 100), 
				y - 50 + Random::GetInstance()->RandomInt(0, 100) );
		}
	}
}

void ItemManager::DropItems(wstring key, float x, float y)
{
	//�������� �����ϰ� ����Ѵ�
	Item* item = new Item(key, x, y);
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

				//�÷��̾�� ������ �浹 ó��
				if (IntersectRect(&rc, &itemsRc, &playerRc))
				{
					//�κ��丮�� ��� �־��ٱ?
					PutInInventory(((Item*)items[i])->GetKeyName());
					//������ ������
					items[i]->SetIsDestroy(true);
				}
			}
		}
	}
}

void ItemManager::PutInInventory(wstring key)
{
	if (mItemInventoryList.find(key) == mItemInventoryList.end()) { //ó�� ����
		//������ ����Ʈ ���� �� �κ��丮���� �ҷ��ͼ� ����, �����
		mItemInventoryList.insert(make_pair(key, 1));
	}
	else { //�̹� �ִ� �������� count ����
		int num = mItemInventoryList[key];
		mItemInventoryList[key] = ++num;
	}
}
