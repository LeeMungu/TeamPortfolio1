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

	void PickUpItems();
	void PutInInventory();
};

