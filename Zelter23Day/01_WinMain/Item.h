#pragma once
#include "GameObject.h"
#include "Image.h"

enum class ItemType
{
	Equipment, // ���
	Weapon, // ����
	Gun, // ��
	Bullet, // �Ѿ�
	Food, // ����
	Drink, // ����
	Material, // ���
	structure, //��ġ��/��ֹ�
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

