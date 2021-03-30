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
	mIndexY = 0;
	EndingText* endingText = new EndingText(mIndexY);
	endingText->Init();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, endingText);
	mEndText = endingText;
	mIndexY++;
	mStop = false;
	SoundPlayer::GetInstance()->LoadFromFile(L"EndingBGM", Resources(L"/09_Sound/EndingBGM.mp3"), false);
	SoundPlayer::GetInstance()->Play(L"EndingBGM", 0.5f * SoundPlayer::GetInstance()->GetBgmVolume());
}

void EndingScene::Release()
{
	ObjectManager::GetInstance()->Release();
}

void EndingScene::Update()
{
	if (mStop == false)
	{
		if (mEndText->GetRect().bottom < WINSIZEY - 10 && mIndexY < 55)
		{
			EndingText* endingText = new EndingText(mIndexY);
			endingText->Init();
			ObjectManager::GetInstance()->AddObject(ObjectLayer::TextBox, endingText);
			mEndText = endingText;
			mIndexY++;
		}
		ObjectManager::GetInstance()->Update();
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			mStop = true;
		}
	
	}
	else
	{
		if (Input::GetInstance()->GetKeyDown(VK_SPACE))
		{
			mStop = false;
		}
	}
}

void EndingScene::Render(HDC hdc)
{
	mImage->Render(hdc, 0, 0);
	ObjectManager::GetInstance()->Render(hdc);
	
}
