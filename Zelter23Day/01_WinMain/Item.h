#pragma once
#include "GameObject.h"
#include "Image.h"

enum class ItemType
{
	equipment, // 장비
	weapon, // 무기
	gun, // 총
	bullet, // 총알
	food, // 음식
	drink, // 음료
	material, // 재료
	structure, //설치물/장애물
	heal,
	end,
};
enum class ItemKind {
	drop,
	inventory,
	quickSlot,
	holding,
};

class Item : public GameObject
{
protected:
	Image* mImage;
	ItemType mType;
	wstring mKeyName;
	int mCount;
	ItemKind mItemKind;
	Image* mNumImage;
	bool mIsFirst;
	bool mIsClicking;
	bool mIsSeleted;
	
	float mAngle;
	float mSpeed;
	float mGravity;

	bool mIsPossiblePick;

	float mCreatedTime;
	float mAlpha;

	Image* mWorkslot;
public:
	POINT mPrePosition;

	Item(wstring imageKey, float x, float y, int count = 1 , ItemKind kind = ItemKind::drop);
	Item(wstring imageKey, string name, float x, float y, int count = 1 , ItemKind kind = ItemKind::inventory);
	void Init();
	void Release(); 
	void Update();
	void Render(HDC hdc);

	wstring GetKeyName() { return mKeyName; }
	void SetCount(int n) { mCount = n; }
	int GetCount() { return mCount; }
	void SetKind(ItemKind kind) { mItemKind = kind; }
	ItemType GetType() { return mType; }
	ItemKind GetItemKind() { return mItemKind; }
	bool GetIsClicking() { return mIsClicking; }
	void SetIsClicking(bool b) { mIsClicking = b; }
	void SetIsSelected(bool b) { mIsSeleted = b; }
	bool GetIsSelected() { return mIsSeleted; }

	void DropMovement();
	void NoPickUp();
	bool GetIsPossiblePick() { return mIsPossiblePick; }

	void SetCountMinus(int n);
};

