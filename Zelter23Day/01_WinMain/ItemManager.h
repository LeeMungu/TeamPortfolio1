#pragma once
#include "Item.h"
#include "Inventory.h"
#include "QuickSlot.h"
class Player;
class Pet;
struct SelectedItem {
	//퀵슬롯 선택된 아이템 이미지 type과 count 저장
	wstring key;
	ItemType quickType;
	int count;
};
class ItemManager
{
	Singleton(ItemManager)
private:
	map<wstring, ItemType> mItemImageList; //아이템 이미지 key로 타입을 구분지어줌
	Player* mPlayer;
	Pet* mPet;

	map<wstring, int> mItemInventoryList; //인벤토리 아이템 이미지 key값과 value: count
	
	//아이템이 있는 슬롯 인덱스를 저장할 변수
	int mIndexX, mIndexY, mIndex, mSeletedItemIndex;

	SelectedItem mSelectedItem;

	Inventory* mInventory;
	BagSlot(*mSlotList)[5];
	QuickSlot* mQuickSlot;
	Slot* mQuickSlotList;
	vector<GameObject*> mItems;

	int mInputNum;
	Item* mInputItem;
public:

	ItemManager();

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	ItemType SetItemType(wstring key);

	void randomItem(wstring objectKey, float x, float y);
	void DropItems(wstring key, float x, float y, int count = 1);
	void PickUpItems();

	void PutInInventory(wstring key, int count);

	void MoveItems();
	//void IntersectInventory(int j, int k);
	//void IntersectQuickSlot(int indexQ);

	void ItemRePositioning();
	void QuickSlotRePositioning(int num);
	void UseQuickSlot(int num);

	//아이템 인벤토리 리스트 리턴
	map<wstring, int> GetmItemInventoryList() { return mItemInventoryList; }
	//플레이어에서 받을 퀵슬롯에서 선택된 아이템 정보를 가져옴
	SelectedItem GetSelectedItem() { return mSelectedItem; }

	void ItemCountCheck(Item* item, int y, int x);
	void SetmItemListCount(wstring wstr, int count) { mItemInventoryList[wstr] = count; }
	POINT GetInventoryIndex(Item* item);
};

