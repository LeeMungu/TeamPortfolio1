#pragma once
#include "GameObject.h"

#define TileCountX 9
#define TileCountY 9
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
class Image;
class HousingObject : public GameObject
{
	
	vector<vector<Tile*>> mTileList;
	SideType sidetype;
	Image* mInSideImage;
	Image* mRoofSideImage;

public:
	HousingObject(const string& name, float x, float y,SideType type);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

