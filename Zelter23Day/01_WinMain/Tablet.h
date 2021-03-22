#pragma once
#include "UI.h"

class Image;

enum class Status
{
	Char_Status,
	Companion,
	MakeTool,
};


class Tablet : public UI
{
	Image* mBaseImage;
	Image* CharStatusIcon;
	Image* CompanionIcon;
	Image* MakeToolIcon;

	bool mIsOpened;

public:
	Tablet(const string& name);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetOpened(bool b) { mIsOpened = b; }




};

