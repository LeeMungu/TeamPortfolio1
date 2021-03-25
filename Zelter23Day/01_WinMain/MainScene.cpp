#include "pch.h"
#include "MainScene.h"
#include "Image.h"
#include "Button.h"

void MainScene::Init()
{
	mImage = ImageManager::GetInstance()->FindImage(L"LoadingCat");
	mStartButton = new Button(L"살아남기", WINSIZEX / 5*2, WINSIZEY / 5 * 3,200,70, []() {SceneManager::GetInstance()->LoadScene(L"LoadingScene"); });
	mToolSceneButton = new Button(L"작업장", WINSIZEX / 5 * 3, WINSIZEY / 5 * 3,200,70, []() {SceneManager::GetInstance()->LoadScene(L"MapToolScene"); });
}

void MainScene::Release()
{
	SafeDelete(mStartButton);
	SafeDelete(mToolSceneButton);
}

void MainScene::Update()
{

	mStartButton->Update();
	if (mToolSceneButton != nullptr)
	{
		mToolSceneButton->Update();
	}
}

void MainScene::Render(HDC hdc)
{
	mImage->Render(hdc, 0, 0);
	mStartButton->Render(hdc);
	mToolSceneButton->Render(hdc);
}
