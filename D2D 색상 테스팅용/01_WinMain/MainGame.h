#pragma once
#include "GameObject.h"
class Image;

class MainGame
{
	Image* mImage;
	float mAngle;
	ID2D1BitmapRenderTarget* mFirstBuffer;
	float mR, mG, mB, mA;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
