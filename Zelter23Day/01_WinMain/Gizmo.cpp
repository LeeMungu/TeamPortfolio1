#include "pch.h"
#include "Gizmo.h"

Gizmo::Gizmo()
{
	mNullBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

	HPEN redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN bluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	HPEN blackpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN purplepen = CreatePen(PS_SOLID, 1, RGB(186, 0, 255));
	HPEN mintpen = CreatePen(PS_SOLID, 1, RGB(0, 255, 216));

	HPEN redPen2 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN greenPen2 = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	HPEN bluePen2 = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	HPEN blackpen2 = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN purplepen2 = CreatePen(PS_SOLID, 2, RGB(186, 0, 255));
	HPEN mintpen2 = CreatePen(PS_SOLID, 2, RGB(0, 255, 216));

	mPenList.insert(make_pair(Color::Red, redPen));
	mPenList.insert(make_pair(Color::Green, greenPen));
	mPenList.insert(make_pair(Color::Blue, bluePen));
	mPenList.insert(make_pair(Color::Black, blackpen));
	mPenList.insert(make_pair(Color::Purple, purplepen));
	mPenList.insert(make_pair(Color::Mint, mintpen));

	mPenList.insert(make_pair(Color::Red2, redPen));
	mPenList.insert(make_pair(Color::Green2, greenPen));
	mPenList.insert(make_pair(Color::Blue2, bluePen));
	mPenList.insert(make_pair(Color::Black2, blackpen));
	mPenList.insert(make_pair(Color::Purple2, purplepen));
	mPenList.insert(make_pair(Color::Mint2, mintpen));
}

Gizmo::~Gizmo()
{
	PenIter iter = mPenList.begin(); 
	for (; iter != mPenList.end(); ++iter)
	{
		DeleteObject(iter->second);
	}
	DeleteObject(mNullBrush);
}

void Gizmo::DrawRect(HDC hdc, RECT rc, Color color)
{
	HPEN pen = mPenList[color];

	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc,mNullBrush);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	RenderRect(hdc, rc);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}

void Gizmo::DrawEllipse(HDC hdc, float x, float y, float radius, Color color)
{
	HPEN pen = mPenList[color];

	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, mNullBrush);
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	RenderEllipse(hdc, x,y,radius);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
}
