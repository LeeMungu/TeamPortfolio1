#pragma once

/*
1. �ִϸ��̼� 
2. �̺�Ʈ ����� ��
*/

class Image;

class MainGame
{
	
	//���� ���� test
	ID2D1BitmapRenderTarget* mFirstBuffer;
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	void RenderTime(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

