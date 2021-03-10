#include "pch.h"
#include "Tile.h"
#include "Image.h"
#include "Camera.h"

Tile::Tile(Image * image, float x, float y, float sizeX, float sizeY, int frameIndexX, int frameIndexY)
{
	mImage = image;
	mX = x;
	mY = y;
	mSizeX = sizeX;
	mSizeY = sizeY;
	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mFrameIndexX = frameIndexX;
	mFrameIndexY = frameIndexY;
}


void Tile::Render(HDC hdc)
{
	if (mTileLayer == TileLayer::PalletteType)
	{
		mImage->FrameRender(hdc, mX, mY, mFrameIndexX, mFrameIndexY);
	}
	else
	{
		//RenderRect(hdc, mRect);
		if (mImage != nullptr)
			CameraManager::GetInstance()->GetMainCamera()->ScaleFrameRender(hdc,
				mImage, mRect.left, mRect.top, mFrameIndexX, mFrameIndexY, mSizeX, mSizeY);

		RECT tempRc = RectMake(mX - CameraManager::GetInstance()->GetMainCamera()->GetRect().left,
			mY - CameraManager::GetInstance()->GetMainCamera()->GetRect().top,
			mSizeX, mSizeY);

		Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Red);

		if (Input::GetInstance()->GetKey(VK_LCONTROL))
		{
			if (mTileLayer == TileLayer::normal)
				Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Green);
			if (mTileLayer == TileLayer::wall)
				Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Red);
			if (mTileLayer == TileLayer::slow)
				Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Blue);
		}

		//Gizmo::GetInstance()->DrawRect(hdc, tempRc, Gizmo::Color::Black);
	}
}

void Tile::Move(float x, float y)
{
	mX = x;
	mY = y;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}