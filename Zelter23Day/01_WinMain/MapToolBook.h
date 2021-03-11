#pragma once
#include "GameObject.h"
enum class BookType : int
{
	Tile = 0,
	House = 1,
	InterectObject = 2,
	NoninterectObject = 3,
	End
};



class Button;
class HousingObject;
class MapToolBook : public GameObject
{
	class Image* mImage;
	class Animation* mAnimation;
	vector<vector<class Tile*>> mPallete;
	float mSpeed;
	//버튼 형변환
	BookType mBookType;
	bool mIsTypeChange;
	//버튼
	Button* mTileButton;
	Button* mHouseButton;
	Button* mInterectObjectButton;
	Button* mNoninterectObjectButton;

	HousingObject* mHouseObject;
	int mNowTileCountX;
	int mNowTileCountY;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void ChangeMode(BookType bookType);
	vector<vector<Tile*>> GetPalleteList() const { return mPallete; }

	int GetNowTilecountX() {return mNowTileCountX;}
	int GetNowTilecountY() { return mNowTileCountY; }
};

