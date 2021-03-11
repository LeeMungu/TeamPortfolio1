#pragma once
#include "D2DRenderer.h"

inline RECT RectMake(int x, int y, int width, int height)
{
	return { x,y,x + width, y + height };
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	return { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
}

inline RECT RectMakeBottom(int x, int y, int width, int height)
{
	RECT result;
	result.left = x - width / 2;
	result.right = x + width / 2; 
	result.top = y - height;
	result.bottom = y;
	return result;
}

inline void RenderRect(HDC hdc, RECT rc)
{
	ID2D1RenderTarget* renderTarget = D2DRenderer::GetInstance()->GetRenderTarget();

	
	ID2D1SolidColorBrush* brush;
	D2D1_COLOR_F color;
	//r,g,b,a
	color = { 0.0f,0.0f,0.0f,1.0f };
	renderTarget->CreateSolidColorBrush(color, &brush);

	//얜 일단 놔두고
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	D2D1_RECT_F rect = { rc.left,rc.top,rc.right,rc.bottom };

	renderTarget->DrawRectangle(rect, brush);

	brush->Release();
	/*
	DrawRectangle(
		CONST D2D1_RECT_F & rect,
		_In_ ID2D1Brush * brush,
		FLOAT strokeWidth = 1.0f,
		_In_opt_ ID2D1StrokeStyle * strokeStyle = NULL
	)
	*/
	//Rectangle(hdc, rc.left,rc.top,rc.right,rc.bottom);
}

inline void RenderEllipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//원이 가지고 있는 구성요소 : 중심점, 반지름
inline void RenderEllipse(HDC hdc,int x, int y, int radius)
{
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
}

inline void RenderLine(HDC hdc,int startX, int startY, int endX, int endY)
{
	ID2D1RenderTarget* renderTarget = D2DRenderer::GetInstance()->GetRenderTarget();

	D2D_POINT_2F start = D2D1::Point2F(startX, startY);
	D2D_POINT_2F end = D2D1::Point2F(endX, endY);

	ID2D1SolidColorBrush* brush;
	D2D1_COLOR_F color;
	//r,g,b,a
	color = { 0.0f,0.0f,0.0f,1.0f };
	renderTarget->CreateSolidColorBrush(color, &brush);

	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	renderTarget->DrawLine(start, end, brush, 1.0f);

	brush->Release();
	
	//기존 렌더방식
	//MoveToEx(hdc, startX, startY, NULL);
	//LineTo(hdc, endX, endY);
}

inline float GetDistance(int aX, int aY, int bX, int bY)
{
	float width = aX - bX;
	float height = aY - bY;

	return sqrtf(width * width + height * height);
}

inline bool IntersectRectToCircle(RECT rc, int x, int y, int radius)
{
	if ((rc.left <= x && x <= rc.right) ||
		(rc.top <= y && y <= rc.bottom))
	{
		RECT newRect = rc;
		newRect.left -= radius;
		newRect.right += radius;
		newRect.top -= radius;
		newRect.bottom += radius;

		if ((newRect.left <= x && x <= newRect.right) &&
			(newRect.top <= y && y <= newRect.bottom))
		{
			return true;
		}
	}
	

	//꼭지점 비교
	//좌상단
	if (radius >= GetDistance(x, y, rc.left, rc.top))return true;
	//우상단
	if (radius >= GetDistance(x, y, rc.right, rc.top))return true;
	//좌하단
	if (radius >= GetDistance(x, y, rc.left, rc.bottom))return true;
	//우하단
	if (radius >= GetDistance(x, y, rc.right, rc.bottom))return true;

	//코드가 여기까지 도달했다는 것은 위에 조건에 한번도 걸리지 않았다는 것
	//충돌하지 않았다
	return false;
}