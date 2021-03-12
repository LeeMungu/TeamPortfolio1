#include "pch.h"
#include "LoadingScene.h"
#include "Image.h"

void LoadingScene::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}

void LoadingScene::Init()
{
	mLoadIndex = 0;
	mIsEndLoading = false;

	//이미지 (플레이어)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"PlayerRun", Resources(L"Player_run.png"),7,4); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"PlayerWalk", Resources(L"Player_walk.png"), 7, 4); });

	//이미지 (몬스터)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"MonsterRun", Resources(L"zombie01.png"), 5, 6); });

	//이미지 (오브젝트)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bench1", Resources(L"Bench1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bench2", Resources(L"Bench2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bench1", Resources(L"Bench1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus1", Resources(L"Bus1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus2", Resources(L"Bus2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus3", Resources(L"Bus3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus4", Resources(L"Bus4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus5", Resources(L"Bus5.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus6", Resources(L"Bus6.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus7", Resources(L"Bus7.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus8", Resources(L"Bus8.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus9", Resources(L"Bus9.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus10", Resources(L"Bus10.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus11", Resources(L"Bus11.png"), 2, 1); });




}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
	if (mLoadIndex >= mLoadList.size())
	{
		mIsEndLoading = true;
		return;
	}

	function<void(void)> func = mLoadList[mLoadIndex];
	func();
	mLoadIndex++;
}

void LoadingScene::Render(HDC hdc)
{
	mLoadingImage->Render(hdc, 0, 0);
}
