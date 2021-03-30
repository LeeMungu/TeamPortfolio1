#include "pch.h"
#include "EndingScene.h"
#include "EndingText.h"
#include "BackGround.h"
#include "Image.h"

void EndingScene::Init()
{
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"EndingBackGround", Resources(L"/01_UI/EndingBackGround.png"));
	//BackGround* backGround = new BackGround("EndingBackGround", WINSIZEX / 2, WINSIZEY / 2);
	//backGround->Init();
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Background, backGround);
	mImage = IMAGEMANAGER->FindImage(L"EndingBackGround");
	//mIndexY = 0;
	//EndingText* endingText = new EndingText(mIndexY);
	//endingText->Init();
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, endingText);
	//mEndText = endingText;
	//mIndexY++;
	//mStop = false;
	SoundPlayer::GetInstance()->LoadFromFile(L"EndingBGM", Resources(L"/09_Sound/EndingBGM.mp3"), false);
	SoundPlayer::GetInstance()->Play(L"EndingBGM", 0.5f * SoundPlayer::GetInstance()->GetBgmVolume());

	mTextSpeed = 20.f;
	mTextSize = 70;
	mTextX = WINSIZEX / 6;
	mTextY = WINSIZEY;
	mTextInterval = mTextSize * 1.5f;
}

void EndingScene::Release()
{
	ObjectManager::GetInstance()->Release();
}

void EndingScene::Update()
{
	mTextY -= mTextSpeed * (Time::GetInstance()->DeltaTime());
}

void EndingScene::Render(HDC hdc)
{
	mImage->Render(hdc, 0, 0);
	//ObjectManager::GetInstance()->Render(hdc);
	TextRender(L"Team 23ÀÏ ÈÄ", 0);
	TextRender(L"", 1);
	TextRender(L"CTO  ±è¹ÎÂù", 2);
	TextRender(L"Á¶Àå  ÀÌ¹®±¸", 3);
	TextRender(L"Á¶¿ø  ÃÖÁö¿ø", 4);
	TextRender(L"Á¶¿ø  ±èÁ¾ÈÆ", 5);
	TextRender(L"Á¶¿ø  ÀÌÁöÈÆ", 6);
	TextRender(L"", 7);
	TextRender(L"Thanks for Playing", 8);
	
}


void EndingScene::TextRender(wstring key, int num)
{
	D2DRenderer::GetInstance()->RenderText(mTextX + 7, mTextY + num * mTextInterval + 7, key, mTextSize, DefaultBrush::Black);
	D2DRenderer::GetInstance()->RenderText(mTextX, mTextY + num * mTextInterval, key, mTextSize, DefaultBrush::White);
}
