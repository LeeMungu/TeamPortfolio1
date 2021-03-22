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
	
	if (str == L"Ben") { //��ġ - ��������
		key = L"WoodBrench1";
	}
	else if (str == L"Bus") { //����
		key = L"Iron1";
	}
	else if (str == L"Cab") { //ĳ���

	}
	else if (str == L"Car") { //�ڵ���

	}
	else if (str == L"Cha") { //����

	}
	else if (str == L"Clo") { //����

	}
	else if (str == L"Com") { //��ǻ��

	}
	else if (str == L"Dea") { //dead tree

	}
	else if (str == L"Des") { //å��

	}
	else if (str == L"dis") { //���Ҽ�

	}
	else if (str == L"Dol") { //����

	}
	else if (str == L"Dus") { //����Ʈ �ڽ�

	}
	else if (str == L"Fan") { //��ǳ��

	}
	else if (str == L"Han") { //�����

	}
	else if (str == L"Mot") { //�������

	}
	else if (str == L"Pla") {

	}
	else if (str == L"Ref") { //�����

	}
	else if (str == L"Roc") { //��

	}
	else if (str == L"She") { //����

	}
	else if (str == L"Sho") {
		wstring str2 = objectKey.substr(3, 1);
		if (str2 == L"e") { //�Ź���

		}
		else { //�����̽�

		}
	}
	else if (str == L"Sig") { //������

	}
	else if (str == L"Sof") { //����

	}
	else if (str == L"Suv") { //suv �ڵ���

	}
	else if (str == L"Tab") { //���̺�

	}
	else if (str == L"Toi") { //����

	}
	else if (str == L"Tre") { //����
		key = L"WoodBrench1";
	}
	else if (str == L"Tru") { //Ʈ��

	}
	else if (str == L"Tv1") { //tv

	}
	else if (str == L"Was") { //��Ź��

	}
	else if (str == L"Wat") { //�ļ���

	}
	else if (str == L"Wor") { //�۾���

	}
	else if (str == L"Zom") { //����

	}
	//��� ���� ����
	DropItems(key, x, y);
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
	vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Item);

	if (items.size() != NULL)
	{
		for (int i = 0; i < items.size(); ++i) {
			RECT rc;
			RECT itemsRc = ((Item*)items[i])->GetRect();
			RECT playerRc = mPlayer->GetRect();
			
			//�÷��̾�� ������ �浹 ó��
			if (IntersectRect(&rc, &itemsRc, &playerRc)) {
				//�κ��丮�� ��� �־��ٱ?
				PutInInventory();
				//������ ������
				items[i]->SetIsDestroy(true);
			}
		}
	}
}

void ItemManager::PutInInventory()
{

}
