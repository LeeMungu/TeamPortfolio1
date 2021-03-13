#pragma once
#include "Scene.h"
#include "Tile.h"
#include "Image.h"
#include "MapToolBook.h"
#include <stack>

//0. 타일 이미지 다른걸로 해라
//1. 한 타일당 한줄( , 로 구분)
//2. 되돌리기 기능 구현
//3. 상당히 이쁘게 만들기

class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Undo() = 0;
};

class IBrushTile : public ICommand
{
	Tile* mTargetTile;

	wstring mSaveImageKey;
	int mSaveFrameX;
	int mSaveFrameY;

	Tile* mExecutePalleteData;
public:
	IBrushTile(Tile* tile ,Tile* executeData)
	{
		mTargetTile = tile;
		mExecutePalleteData = executeData;

		if(tile->mImage != nullptr)
			mSaveImageKey = tile->mImage->GetKey();
		mSaveFrameX = tile->mFrameIndexX;
		mSaveFrameY = tile->mFrameIndexY;
	}

	void Execute()
	{
		mTargetTile->mImage =
			ImageManager::GetInstance()->FindImage(mExecutePalleteData->mImage->GetKey());
		mTargetTile->mFrameIndexX = mExecutePalleteData->mFrameIndexX;
		mTargetTile->mFrameIndexY = mExecutePalleteData->mFrameIndexY;
	}
	void Undo()override
	{
		mTargetTile->mImage = ImageManager::GetInstance()->FindImage(mSaveImageKey);
		mTargetTile->mFrameIndexX = mSaveFrameX;
		mTargetTile->mFrameIndexY = mSaveFrameY;
	}
};

enum ToolMode
{
	Pallete,
	Type,
	ToolEnd
};


class Button;
class Player;
class MapToolScene : public Scene
{
	//타일 총 갯수
	int mTileCountX;
	int mTileCountY;
	//선택한시점의 인덱스
	int mPickStartIndexX;
	int mPickStartIndexY;
	bool mIsExtendTile;

	//드래그엔드롭 색칠하기
	int mChangeStartIndexX;
	int mChangeStartIndexY;
	int mChangeEndIndexX;
	int mChangeEndIndexY;
	bool mIsChangingTile; //색칠하는 중인지 여부

	//class Tile* mTileList[TileCountY][TileCountX];
	vector<vector<class Tile*>> mTileList;
	MapToolBook* mToolBook;

	Tile* mCurrentPallete;
	class Tile* mTile;

	Button* mSaveButton;
	Button* mLoadButton;

	TileLayer mCurrentLayer;

	stack<ICommand*> mCommandList;
	stack<ICommand*> mRedoList;

	Player* player;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


private:
	void Save();
	void Load();

	void MakeNormal();
	void MakeSlow();
	void MakeWall();

	void PushCommand(ICommand* command);
	void Undo();
};

