#include "pch.h"
#include "Tile.h"
#include "Image.h"
#include "Camera.h"

Tile::Tile(Image * image, float x, float y, float sizeX, float sizeY, int frameIndexX, int frameIndexY, int indexX, int indexY)
{
	mImage = image;
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mFrameIndexX = frameIndexX;
	mFrameIndexY = frameIndexY;
	mIndexX = indexX;
	mIndexY = indexY;
}


void Tile::Render(HDC hdc)
{
	//파레트일때
	if (mTileLayer == TileLayer::PalletteType)
	{
		mImage->ScaleFrameRender(hdc, mRect.left, mRect.top, mFrameIndexX, mFrameIndexY, mSizeX, mSizeY);
		Gizmo::GetInstance()->DrawRect(hdc, mRect, Gizmo::Color::Blue);
	}
	//타일일때
	else
	{
		if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mRect))
		{
			//RenderRect(hdc, mRect);
			if (mImage != nullptr)
			{
				CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc,
					mImage, mRect.left, mRect.top, mFrameIndexX, mFrameIndexY, mSizeX, mSizeY);
			}
			//기즈모 외곽선 그리기
			RECT tempRc = RectMake(mRect.left - CameraManager::GetInstance()->GetMainCamera()->GetRect().left,
				mRect.top - CameraManager::GetInstance()->GetMainCamera()->GetRect().top,
				mSizeX, mSizeY);
			if (PtInRect(&tempRc, _mousePosition))
			{
				Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Red2);
			}
			else
			{
				//Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Green);
			}

			//컨트롤키로 속성 표시
			if (Input::GetInstance()->GetKey(VK_LCONTROL))
			{
				if (mTileLayer == TileLayer::normal)
					Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Green);
				if (mTileLayer == TileLayer::wall)
					Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Red2);
				if (mTileLayer == TileLayer::slow)
					Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Blue2);
			}

			//Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Black);
		}
	}
}

void Tile::Move(float x, float y)
{
	mX = x;
	mY = y;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
}