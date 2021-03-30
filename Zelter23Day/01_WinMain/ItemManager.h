#pragma once
#include "Item.h"
#include "Inventory.h"
#include "QuickSlot.h"
class Player;
class Pet;
struct SelectedItem {
	//������ ���õ� ������ �̹��� type�� count ����
	wstring key;
	ItemType quickType;
	int count;
};
class ItemManager
{
	Singleton(ItemManager)
private:
	map<wstring, ItemType> mItemImageList; //������ �̹��� key�� Ÿ���� ����������
	Player* mPlayer;
	Pet* mPet;

	map<wstring, int> mItemInventoryList; //�κ��丮 ������ �̹��� key���� value: count
	
	//�������� �ִ� ���� �ε����� ������ ����
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

	//������ �κ��丮 ����Ʈ ����
	map<wstring, int> GetmItemInventoryList() { return mItemInventoryList; }
	//�÷��̾�� ���� �����Կ��� ���õ� ������ ������ ������
	SelectedItem GetSelectedItem() { return mSelectedItem; }

	void ItemCountCheck(Item* item, int y, int x);
	void SetmItemListCount(wstring wstr, int count) { mItemInventoryList[wstr] = count; }
	POINT GetInventoryIndex(Item* item);
};

