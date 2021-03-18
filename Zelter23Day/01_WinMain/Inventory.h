#pragma once
#include "UI.h"
class Image;
class Inventory : public UI
{
	Image* mBaseImage;
	bool mIsOpened;
public:
	Inventory(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetOpened(bool b) { mIsOpened = b; }
};

