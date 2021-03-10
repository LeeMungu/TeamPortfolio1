#pragma once
#include "GameObject.h"



//구조체 변수는 대문자로 시작하게 짬, 나같은경우에는
struct TilePallete
{
	class Image* Image;
	int PositionX;
	int PositionY;
	int Width;
	int Height;
	RECT Rc;
	int FrameX;
	int FrameY;
};

class MapToolBook : public GameObject
{
	class Image* mImage;
	class Animation* mAnimation;
	vector<vector<class Tile*>> mPallete;
	float mSpeed;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	vector<vector<Tile*>> GetPalleteList() const { return mPallete; }
};

