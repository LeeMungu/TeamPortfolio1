#pragma once
#include "UI.h"
class Image;
class Item;
class Button;
class WorkTable : public UI
{
	Image* mWorkTable;
	Image* mNumImage;
	


	Button* mStartBtn;
	Button* mTimeUpBtn;
	Button* mTimeDownBtn;

	bool mIsTableOpen;
	bool mIsOpenTrigger;

	Button* mMakeWoodBoard;
	bool mIsMakingOpen;

	int mMakingCount;
	int mMakingTotalCount;
public:
	WorkTable(const string& name);
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	bool GetTableOpen() { return mIsTableOpen; }
	void SetTableOpen(bool istable) { mIsTableOpen = istable; }
	void DeleteItem();

	void Worktemplet();
	void UpdateButton();
	void MakingItem();
};

