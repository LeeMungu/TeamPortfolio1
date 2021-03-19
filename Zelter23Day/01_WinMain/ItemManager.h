#pragma once
class Player;
class ItemManager
{
	Singleton(ItemManager)

public:
	Player* mPlayer;

	void Init();
	void Update();

	void PickUpItems();
	void PutInInventory();
};

