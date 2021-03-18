#pragma once
#include "GameObject.h"
#include "Image.h"

enum class ItemType
{
	Equipment, // 장비
	Weapon, // 무기
	Food, // 음식
	Drink, // 음료
	Material // 재료

};

class Item : public GameObject
{
protected:
	Image* mImage;
	ItemType mType;
	wstring mKeyName;
public:
	Item(wstring imageKey, float x, float y, ItemType type);
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);



};

