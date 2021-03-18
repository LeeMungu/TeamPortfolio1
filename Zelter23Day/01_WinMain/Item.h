#pragma once
#include "GameObject.h"
#include "Image.h"

enum class ItemType
{
	Equipment, // ���
	Weapon, // ����
	Food, // ����
	Material // ���

};

class Item : GameObject
{
protected:
	Image* mImage;
	int mIndexX;
	int mIndexY;
	int mFrameCount;


public:
	void Init(float x, float y, ItemType type);
	void Release();
	void Update();
	void Render(HDC hdc);



};

