#pragma once
#include "UI.h"
class Image;
class Item;
class Button;
class WorkTable : public UI
{
	Image* mWorkTable;

	Button* mStartBtn;
	Button* mTimeUpBtn;
	Button* mTimeDownBtn;

	bool mIsTableOpen;

public:
	WorkTable(const string& name);
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

