#include "pch.h"
#include "ItemManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Item.h"
ItemManager::ItemManager()
{
	mItemImageList.insert(make_pair(L"Revolver", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"Arrow", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"Blade", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"CrossBow", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"CrowBar", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"IronAxe", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"IronHammer", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"Pipe", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"PistolBullet", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"Rifle", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"Rifle2", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"RifleBullet", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"Shotgun", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"ShotgunBullet", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"SMGBullet", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"StoneAxe", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"StoneHammer", ItemType::Weapon));
	mItemImageList.insert(make_pair(L"Torch", ItemType::Weapon));

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
	mItemImageList.insert(make_pair(L"Cup", ItemType::Material));//drink�ƴѰ�
	mItemImageList.insert(make_pair(L"Iron1", ItemType::Material));
	mItemImageList.insert(make_pair(L"Iron2", ItemType::Material));
	mItemImageList.insert(make_pair(L"Steel", ItemType::Material));
	mItemImageList.insert(make_pair(L"Stone1", ItemType::Material));


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
	mItemImageList.insert(make_pair(L"WoodBoard", ItemType::structure));
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

void ItemManager::PickUpItems()
{
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
