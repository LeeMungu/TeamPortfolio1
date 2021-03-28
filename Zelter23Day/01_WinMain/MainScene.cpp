#include "pch.h"
#include "MainScene.h"
#include "Image.h"
#include "Button.h"
#include "GameEvent.h"

void MainScene::Init()
{
	mIsSkip = false;

	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		mIsSkip = true;
	}
	if (mIsSkip == true)
	{
		GameEventManager::GetInstance()->RemoveAllEvent();
		GameEventManager::GetInstance()->PushEvent(new IDelayFunEvent(7.f, [this]() {
			mImage = ImageManager::GetInstance()->FindImage(L"LoadingCat");
			mStartButton = new Button(L"살아남기", WINSIZEX / 5 * 2, WINSIZEY / 5 * 3, 200, 70, []() {SceneManager::GetInstance()->LoadScene(L"LoadingScene"); });
			mToolSceneButton = new Button(L"작업장", WINSIZEX / 5 * 3, WINSIZEY / 5 * 3, 200, 70, []() {SceneManager::GetInstance()->LoadScene(L"MapToolLoadingScene"); });
		}));
		mImage = ImageManager::GetInstance()->FindImage(L"PrologueImage1");
	}
	if (mIsSkip == false)
	{
		GameEventManager::GetInstance()->RemoveAllEvent();
 		GameEventManager::GetInstance()->PushEvent(new IDelayFunEvent(7.f, [this]() {
			mImage = ImageManager::GetInstance()->FindImage(L"PrologueImage2");

			SoundPlayer::GetInstance()->Play(L"KakaoTalkSound", 0.8f
				* SoundPlayer::GetInstance()->GetEffectVolume());
		}));


		GameEventManager::GetInstance()->PushEvent(new IDelayFunEvent(7.f, [this]() {
			mImage = ImageManager::GetInstance()->FindImage(L"LoadingCat");
			mStartButton = new Button(L"살아남기", WINSIZEX / 5 * 2, WINSIZEY / 5 * 3, 200, 70, []() {SceneManager::GetInstance()->LoadScene(L"LoadingScene"); });
			mToolSceneButton = new Button(L"작업장", WINSIZEX / 5 * 3, WINSIZEY / 5 * 3, 200, 70, []() {SceneManager::GetInstance()->LoadScene(L"MapToolLoadingScene"); });
		}));
		mImage = ImageManager::GetInstance()->FindImage(L"PrologueImage1");

		SoundPlayer::GetInstance()->Play(L"Siren1", 0.6f * SoundPlayer::GetInstance()->GetBgmVolume());
	}

}

void MainScene::Release()
{
	GameEventManager::GetInstance()->RemoveAllEvent();
	SafeDelete(mStartButton);
	SafeDelete(mToolSceneButton);
}

void MainScene::Update()
{
	GameEventManager::GetInstance()->Update();
	if (mStartButton != nullptr)
	{
		mStartButton->Update();
	}
	if (mToolSceneButton != nullptr)
	{
		mToolSceneButton->Update();
	}
}

void MainScene::Render(HDC hdc)
{
	mImage->Render(hdc, 0, 0);
	if (mStartButton != nullptr)
	{
		mStartButton->Render(hdc);
	}
	if (mToolSceneButton != nullptr)
	{
		mToolSceneButton->Render(hdc);
	}
}
