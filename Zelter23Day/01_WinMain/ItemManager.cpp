#include "pch.h"
#include "ItemManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Item.h"
void ItemManager::Init()
{
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
}

void ItemManager::Update()
{
	PickUpItems();
}

void ItemManager::PickUpItems()
{
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
