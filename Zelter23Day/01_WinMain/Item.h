#pragma once
#include "GameObject.h"
#include "Image.h"

enum class ItemType
{
	Equipment, // 장비
	Weapon, // 무기
	Gun, // 총
	Bullet, // 총알
	Food, // 음식
	Drink, // 음료
	Material, // 재료
	structure, //설치물/장애물
};
enum class ItemKind {
	drop,
	inventory,
};

class Item : public GameObject
{
protected:
	Image* mImage;
	ItemType mType;
	wstring mKeyName;
	int mCount;
	ItemKind mItemKind;
public:
	Item(wstring imageKey, float x, float y, int count = 1 , ItemKind kind = ItemKind::drop);
	void Init();
	void Release(); 
	void Update();
	void Render(HDC hdc);

	wstring GetKeyName() { return mKeyName; }
};

