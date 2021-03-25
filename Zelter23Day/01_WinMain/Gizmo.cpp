#include "pch.h"
#include "Gizmo.h"

Gizmo::Gizmo()
{
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
	if (color == Color::Red)
		RenderRect(hdc, rc, 1.0f, 0, 0);
	else if (color == Color::Green)
		RenderRect(hdc, rc, 0, 1.0f, 0);
	else if (color == Color::Blue)
		RenderRect(hdc, rc, 0, 0, 1.0f);
	else if (color == Color::Red2)
		RenderRect(hdc, rc, 1.0f, 0, 0, 5.f);
	else if (color == Color::Green2)
		RenderRect(hdc, rc, 0, 1.0f, 0, 5.f);
	else if (color == Color::Blue2)
		RenderRect(hdc, rc, 0, 0, 1.0f, 5.f);
	else if (color == Color::Mint)
		RenderRect(hdc, rc, 33.f / 255.f, 189.f / 255.f, 153.f / 255.f);
	else if (color == Color::Mint2)
		RenderRect(hdc, rc, 33.f / 255.f, 189.f / 255.f, 153.f / 255.f, 5.f);
	else if (color == Color::Purple)
		RenderRect(hdc, rc, 97.f / 255.f, 28.f / 255.f, 161.f / 255.f);
	else if (color == Color::Purple2)
		RenderRect(hdc, rc, 97.f / 255.f, 28.f / 255.f, 161.f / 255.f, 5.f);
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
