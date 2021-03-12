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
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"PlayerRun", Resources(L"/03_Player/Player_run.png"),7,4); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"PlayerWalk", Resources(L"/03_Player/Player_walk.png"), 7, 4); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"PlayerAttack", Resources(L"/03_Player/Plauer_attack.png"), 10, 2); });

	//이미지 (플레이어HP UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Heart", Resources(L"/01_UI/Heart_Icon.png"), 12, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"CircleGage_empty", Resources(L"/01_UI/CircleGage_Status.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"CircleGage_full", Resources(L"/01_UI/CircleGage_Status-Full.png")); });

	//이미지 (플레이어 Hunger UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Hunger_icon", Resources(L"/01_UI/Gage_Icon_Hunger.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Hunger_full", Resources(L"/01_UI/Gage_Fill_Hunger.png")); });

	//이미지 (플레이어 Stemina UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Stemina_icon", Resources(L"/01_UI/Gage_Icon_Stemina.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Stemina_full", Resources(L"/01_UI/Gage_Fill_Stemina.png")); });

	//이미지 (플레이어 Thrist UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Thirst_icon", Resources(L"/01_UI/Gage_Icon_Thirst.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Thirst_full", Resources(L"/01_UI/Gage_Fill_Thirst.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Statu_empty", Resources(L"/01_UI/Gage01_Base-resources.png")); });


	//이미지 (SmartWatch UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"SmarWatch_base", Resources(L"/01_UI/SmartWatch_Base.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_glass_dark", Resources(L"/01_UI/SmartWatch_GlassDark.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_glass", Resources(L"/01_UI/SmartWatch_GlassShine.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_morning", Resources(L"/01_UI/Morning.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_night", Resources(L"/01_UI/Night.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"BlackBase", Resources(L"/01_UI/black_base_status.png")); });

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
