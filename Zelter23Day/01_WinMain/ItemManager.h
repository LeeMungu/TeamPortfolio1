#pragma once
#include "Item.h"
class Player;
class ItemManager
{
	Singleton(ItemManager)
private:
	//map<ObjectLayer, vector<class GameObject*>> mItemList;
	map<wstring, ItemType> mItemImageList;
	Player* mPlayer;

	map<wstring, int> mItemInventoryList; //�κ��丮 ������ �̹��� key���� value: count
	int indexX, indexY;
public:

	ItemManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	ItemType SetItemType(wstring key);
	void randomItem(wstring objectKey, float x, float y);
	void DropItems(wstring key, float x, float y);
	void PickUpItems();
	void PutInInventory(wstring key);
	void MoveItems();
	void ItemRePositioning();
	void QuickSlotRePositioning(int num);
	//������ �κ��丮 ����Ʈ ����
	map<wstring, int> GetmItemInventoryList() { return mItemInventoryList; }
};

