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
