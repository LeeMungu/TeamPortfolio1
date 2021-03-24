#include "pch.h"
#include "TextBox.h"
#include "Image.h"
#include "Camera.h"


TextBox::TextBox(const string& name, wstring textContext)
	:UI(name)
{
	mImage;
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mX = WINSIZEX/4;
	mY = WINSIZEY/4*3;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void TextBox::Init()
{

}

void TextBox::Release()
{

}

void TextBox::Update()
{

}

void TextBox::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()
		->ScaleRender(hdc, mImage, mX, mY, mSizeX, mSizeY);
}
