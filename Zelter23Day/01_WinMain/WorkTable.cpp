#include "pch.h"
#include "WorkTable.h"
#include "Image.h"
#include "Item.h"

WorkTable::WorkTable(const string& name)
	:UI(name)
{
	
}

void WorkTable::Init()
{
	mWorkTable = IMAGEMANAGER->FindImage(L"WorkTable");
	mSizeX = mWorkTable->GetFrameWidth() * 2;
	mSizeY = mWorkTable->GetFrameHeight() * 2;
	mStartBtn = IMAGEMANAGER->FindImage(L"WorkTable_start_btn");
	mUpTimerBtn = IMAGEMANAGER->FindImage(L"WorkTable_Timer_up");
	mDownTimerBtn = IMAGEMANAGER->FindImage(L"WorkTable_Timer_down");
	mIsTableOpen = false;
}

void WorkTable::Release()
{
}

void WorkTable::Update()
{

}

void WorkTable::Render(HDC hdc)
{
	mWorkTable->ScaleRender(hdc, mX, mY, 295 * 2, 255 * 2);
}
