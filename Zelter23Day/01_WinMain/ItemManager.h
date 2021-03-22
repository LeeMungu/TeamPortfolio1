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

public:

	ItemManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void randomItem(wstring objectKey, float x, float y);
	void DropItems(wstring key, float x, float y);
	void PickUpItems();
	void PutInInventory();
};

