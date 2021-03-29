#pragma once
#include "Scene.h"
#include "Tile.h"
#include "Image.h"
#include "MapToolScene.h"

class Player;
class Zombie01;
class SmartWatch;
class PlayerHPUI;
class Tablet;
class WorkTable;
class ItemManager;
class Weapon;

#define TileSize 32
#define Pallette 64
#define TileDivideX 6
#define TileDivideY 9


class scene1 : public Scene
{
	class Tile* mTile;
	vector<vector<class Tile*>> mTileList;

	int mTileCountX;
	int mTileCountY;

	TileLayer mCurrentLayer;
	bool mIsGridMode;
	int mLoadingFile;

	Player* mPlayer;
	Zombie01* mZombie01;
	SmartWatch* mSmartWatch;
	PlayerHPUI* mPlayerHPUI;
	Tablet* mTablet;
	ItemManager* mItemManager;
	bool mIsWorkTable;
	int mZombieCount;
	float mZombieCoolTime;
	float mZombieCoolTimer;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void Load();
	void EnemyRespown(float x, float y);

private:

	void SetLoadingFile(int i) { mLoadingFile = i; }
};

