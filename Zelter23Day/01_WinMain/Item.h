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
	bool mIsClicking;
	POINT mPrePosition;
public:
	Item(wstring imageKey, float x, float y, int count = 1 , ItemKind kind = ItemKind::drop);
	void Init();
	void Release(); 
	void Update();
	void Render(HDC hdc);

	wstring GetKeyName() { return mKeyName; }
};

