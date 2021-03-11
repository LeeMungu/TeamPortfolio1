#pragma once
#include "Scene.h"
#include "Tile.h"
#include "Image.h"
#include "MapToolScene.h"

class Player;
class SmartWatch;

#define TileCountX 25
#define TileCountY 25
#define TileSize 32
#define Pallette 64
#define TileDivideX 6
#define TileDivideY 9


class scene1 : public Scene
{
	class Tile* mTile;
	class Tile* mTileList[TileCountY][TileCountX];

	TileLayer mCurrentLayer;
	bool isGridMode;
	int mLoadingFile;

	Player* player;
	SmartWatch* mSmartWatch;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

private:

	void SetLoadingFile(int i) { mLoadingFile = i; }
};

