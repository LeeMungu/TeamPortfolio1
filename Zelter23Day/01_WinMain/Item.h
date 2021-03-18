#pragma once
#include "GameObject.h"
#include "Image.h"

enum class ItemType
{
	Equipment, // ���
	Weapon, // ����
	Food, // ����
	Drink, // ����
	Material // ���

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

