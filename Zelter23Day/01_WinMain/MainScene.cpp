#include "pch.h"
#include "MainScene.h"
#include "Image.h"
#include "Button.h"
#include "GameEvent.h"

void MainScene::Init()
{
	//이미지 (시작화면 버튼 UI)
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"StartButton", Resources(L"/01_UI/StartButton.png"));
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"WorkButton", Resources(L"/01_UI/WorkButton.png"));
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"EndButton", Resources(L"/01_UI/EndButton.png"));


	mIsSkip = false;

		GameEventManager::GetInstance()->RemoveAllEvent();
 		GameEventManager::GetInstance()->PushEvent(new IDelayFunEvent(7.f, [this]() {
			mImage = ImageManager::GetInstance()->FindImage(L"PrologueImage2");

			SoundPlayer::GetInstance()->Play(L"KakaoTalkSound", 0.8f
				* SoundPlayer::GetInstance()->GetEffectVolume());
		}));
		GameEventManager::GetInstance()->PushEvent(new IDelayFunEvent(7.f, [this]() {
			mImage = ImageManager::GetInstance()->FindImage(L"LoadingCat");
			mStartButton = new Button(L"StartButton", WINSIZEX / 5 * 2, WINSIZEY / 5 * 3, 1.5, []() {SceneManager::GetInstance()->LoadScene(L"LoadingScene"); });
			mToolSceneButton = new Button(L"WorkButton", WINSIZEX / 5 * 3, WINSIZEY / 5 * 3, 1.5, []() {SceneManager::GetInstance()->LoadScene(L"MapToolLoadingScene"); });
			mExitButton = new Button(L"EndButton", WINSIZEX / 5 * 2.9, WINSIZEY / 5 * 3, 1.5, []() {WM_CLOSE; });
		}));
		mImage = ImageManager::GetInstance()->FindImage(L"PrologueImage1");

		SoundPlayer::GetInstance()->Play(L"Siren1", 0.6f * SoundPlayer::GetInstance()->GetBgmVolume());
	

}

void MainScene::Release()
{
	GameEventManager::GetInstance()->RemoveAllEvent();
	SafeDelete(mStartButton);
	SafeDelete(mToolSceneButton);
}

void MainScene::Update()
{
	if (Input::GetInstance()->GetKeyDown(VK_SPACE))
	{
		mIsSkip = true;
	}
	if (mIsSkip == true)
	{
		GameEventManager::GetInstance()->RemoveAllEvent();
		GameEventManager::GetInstance()->PushEvent(new IDelayFunEvent(0.f, [this]() {
			mImage = ImageManager::GetInstance()->FindImage(L"LoadingCat");
			mStartButton = new Button(L"StartButton", WINSIZEX / 5 * 1.7, WINSIZEY / 5 * 3, 1.5,[]() {SceneManager::GetInstance()->LoadScene(L"LoadingScene"); });
			mToolSceneButton = new Button(L"WorkButton", WINSIZEX / 5 * 2.3, WINSIZEY / 5 * 3, 1.5, []() {SceneManager::GetInstance()->LoadScene(L"MapToolLoadingScene"); });
			mExitButton = new Button(L"EndButton", WINSIZEX / 5 * 2.9, WINSIZEY / 5 * 3, 1.5, []() {WM_CLOSE; });
		}));
		mIsSkip = false;
	}
	GameEventManager::GetInstance()->Update();
	if (mStartButton != nullptr)
	{
		mStartButton->Update();
	}
	if (mToolSceneButton != nullptr)
	{
		mToolSceneButton->Update();
	}
	if (mExitButton != nullptr)
	{
		WM_CLOSE;
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
	if (mExitButton != nullptr)
	{
		mExitButton->Render(hdc);
	}
}
