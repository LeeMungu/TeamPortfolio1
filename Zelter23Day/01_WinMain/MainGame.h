#pragma once

/*
1. 애니메이션 
2. 이벤트 만드는 법
*/

class Image;

class MainGame
{
	//d2d하면서 더블버퍼 필요없다.
	//Image* mBackBuffer;	//후면버퍼(건들지마라)
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	void RenderTime(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

