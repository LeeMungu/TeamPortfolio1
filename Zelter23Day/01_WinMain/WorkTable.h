#pragma once
#include "UI.h"
class Image;
class Item;

class WorkTable : public UI
{
	Image* mWorkTable;
	Image* mStartBtn;
	Image* mUpTimerBtn;
	Image* mDownTimerBtn;
	bool mIsTableOpen;

public:
	WorkTable(const string& name);
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

