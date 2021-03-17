#pragma once
#include "Player.h"
#include "Item.h"


class ItemManager
{
private:
	Player* mPlayer;
	vector<Item*> mItemList;


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc, float cameraX, float cameraY);


	void SetPlayerPtr(Player* player) { mPlayer = player; }


};

