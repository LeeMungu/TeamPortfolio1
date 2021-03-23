#pragma once
#include "GameObject.h"
#include "Image.h"

enum class ItemType
{
	equipment, // ���
	weapon, // ����
	gun, // ��
	bullet, // �Ѿ�
	food, // ����
	drink, // ����
	material, // ���
	structure, //��ġ��/��ֹ�
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

