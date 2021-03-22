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
	//앞에 세글자로 오브젝트 구분
	wstring str = objectKey.substr(0,3);

	//오브젝트에 따라 랜덤으로 아이템 key를 정해준다
	wstring key;
	
	if (str == L"Ben") { //벤치 - 나뭇가지
		key = L"WoodBrench1";
	}
	else if (str == L"Bus") { //버스
		key = L"Iron1";
	}
	else if (str == L"Cab") { //캐비넷

	}
	else if (str == L"Car") { //자동차

	}
	else if (str == L"Cha") { //의자

	}
	else if (str == L"Clo") { //옷장

	}
	else if (str == L"Com") { //컴퓨터

	}
	else if (str == L"Dea") { //dead tree

	}
	else if (str == L"Des") { //책상

	}
	else if (str == L"dis") { //디스팬서

	}
	else if (str == L"Dol") { //인형

	}
	else if (str == L"Dus") { //더스트 박스

	}
	else if (str == L"Fan") { //선풍기

	}
	else if (str == L"Han") { //세면대

	}
	else if (str == L"Mot") { //오토바이

	}
	else if (str == L"Pla") {

	}
	else if (str == L"Ref") { //냉장고

	}
	else if (str == L"Roc") { //돌

	}
	else if (str == L"She") { //선반

	}
	else if (str == L"Sho") {
		wstring str2 = objectKey.substr(3, 1);
		if (str2 == L"e") { //신발장

		}
		else { //쇼케이스

		}
	}
	else if (str == L"Sig") { //전광판

	}
	else if (str == L"Sof") { //소파

	}
	else if (str == L"Suv") { //suv 자동차

	}
	else if (str == L"Tab") { //테이블

	}
	else if (str == L"Toi") { //변기

	}
	else if (str == L"Tre") { //나무
		key = L"WoodBrench1";
	}
	else if (str == L"Tru") { //트럭

	}
	else if (str == L"Tv1") { //tv

	}
	else if (str == L"Was") { //세탁기

	}
	else if (str == L"Wat") { //식수대

	}
	else if (str == L"Wor") { //작업대

	}
	else if (str == L"Zom") { //좀비

	}
	//재료 개수 랜덤
	DropItems(key, x, y);
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
	vector<GameObject*> items = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Item);

	if (items.size() != NULL)
	{
		for (int i = 0; i < items.size(); ++i) {
			RECT rc;
			RECT itemsRc = ((Item*)items[i])->GetRect();
			RECT playerRc = mPlayer->GetRect();
			
			//플레이어와 아이템 충돌 처리
			if (IntersectRect(&rc, &itemsRc, &playerRc)) {
				//인벤토리에 어떻게 넣어줄까나?
				PutInInventory();
				//아이템 지워줌
				items[i]->SetIsDestroy(true);
			}
		}
	}
}

void ItemManager::PutInInventory()
{

}
