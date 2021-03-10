#pragma once
#include "GameObject.h"

#define TileCountX 25
#define TileCountY 25
#define TileSize 64
#define Pallette 32
#define TileDivideX 6
#define TileDivideY 9

enum class TileLayer : int
{
	normal=0,
	wall=1,
	slow=2,
	PalletteType=3,
	end
};
class Tile : public GameObject
{
public:
	class Image* mImage;
	int mFrameIndexX;
	int mFrameIndexY;
	float mSpeed;
	TileLayer mTileLayer;

	Tile(class Image* image, float x, float y, float sizeX, float sizeY,
		int frameIndexX, int frameIndexY);
	void Render(HDC hdc);
	void Init()override {};
	void Release()override {};
	void Update()override {};
	void Move(float x, float y);


	TileLayer GetTileLayer() { return mTileLayer; }
	void SetTileLayer(TileLayer tilelayer) { mTileLayer = tilelayer; }
	void SetSpeed(float speed) { mSpeed = speed; }
};

