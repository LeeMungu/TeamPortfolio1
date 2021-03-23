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


	map<wstring, int> mItemInventoryList; //인벤토리 아이템 이미지 key값과 value: count

public:

	ItemManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void randomItem(wstring objectKey, float x, float y);
	void DropItems(wstring key, float x, float y);
	void PickUpItems();
	void PutInInventory(wstring key);
	void InventoryItems();
	void PutInQuickSlot();

	//아이템 인벤토리 리스트 리턴
	map<wstring, int> GetmItemInventoryList() { return mItemInventoryList; }
};

