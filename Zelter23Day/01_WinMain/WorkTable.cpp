#include "pch.h"
#include "WorkTable.h"
#include "Image.h"
#include "Item.h"
#include "Button.h"

WorkTable::WorkTable(const string& name)
	:UI(name)
{
	
}

void WorkTable::Init()
{

	mX = WINSIZEX / 2 - 350;
	mY = WINSIZEY / 2 - 250;
	mWorkTable = IMAGEMANAGER->FindImage(L"WorkTable");
	mSizeX = mWorkTable->GetFrameWidth() * 2;
	mSizeY = mWorkTable->GetFrameHeight() * 2;

	mIsTableOpen = false;
	mStartBtn = new Button(L"WorkTable_start_btn", mX, mY, 100, 100, [this]() {});
	mTimeUpBtn = new Button(L"WorkTable_Timer_up", mX, mY-10, 50, 50, [this]() {});
	mTimeDownBtn = new Button(L"WorkTable_Timer_down", mX, mY+10, 50, 50, [this]() {});

}

void WorkTable::Release()
{
}

void WorkTable::Update()
{

}

void WorkTable::Render(HDC hdc)
{
	mWorkTable->ScaleRender(hdc, mX, mY, mSizeX, mSizeY);
}
