#pragma once
#include "GameObject.h"

#define TileCountX 25
#define TileCountY 25
#define TileSize 64
#define Pallette 32
#define TileDivideX 6
#define TileDivideY 9

enum class SideType : int
{
	InSide,
	RoofSide
};

class Tile;
class HousingObject : public GameObject
{
	
	vector<vector<Tile*>> mTileList;
	SideType sidetype;

public:
	HousingObject(const string& name, float x, float y, SideType type);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void Load();
};

