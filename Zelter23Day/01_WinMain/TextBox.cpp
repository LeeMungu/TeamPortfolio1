#include "pch.h"
#include "TextBox.h"
#include "Image.h"
#include "Camera.h"


TextBox::TextBox(wstring textContext)
	:UI("TextBox")
{
	mImage = ImageManager::GetInstance()->FindImage(L"TextBox");
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mX = WINSIZEX/5*2 -100;
	mY = WINSIZEY/4*3 + 50;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mTextContext = textContext;
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
	//텍스트 박스
	mImage->ScaleRender(hdc, mRect.left, mRect.top, mSizeX, mSizeY);
	
	//글씨 출력
	D2DRenderer::GetInstance()->RenderText(
		mRect.left+mSizeX/8, mRect.top+mSizeY/4, mTextContext.c_str(), 25);

}
