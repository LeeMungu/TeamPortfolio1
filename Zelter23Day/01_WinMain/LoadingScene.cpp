#include "pch.h"
#include "LoadingScene.h"
#include "Image.h"
#include "Animation.h"



void LoadingScene::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}

void LoadingScene::Init()
{
	mLoadIndex = 0;
	mIsEndLoading = false;

	//이미지 (플레이어)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Player_run", Resources(L"/03_Player/Player_run.png"), 7, 4); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Player_walk", Resources(L"/03_Player/Player_walk.png"), 7, 4); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Player_attack", Resources(L"/03_Player/Player_attack.png"), 10, 2); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Player_roll", Resources(L"/03_Player/Player_roll.png"), 7, 2); });

	//이미지 (무기 /총)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Weapon_pistol", Resources(L"/03_Player/Weapon_pistol.png"), 1, 1); });

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
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_num", Resources(L"/01_UI/SmartWatchNum.png"), 11, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"SW_AMPM", Resources(L"/01_UI/AMPM.png"), 2, 1); });

	//이미지 (몬스터)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Zombie01", Resources(L"/06_Zombie/zombie01.png"), 5, 6); });

	//이미지 (Active Object)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bench1", Resources(L"/05_Object/Bench1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bench2", Resources(L"/05_Object/Bench2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus1", Resources(L"/05_Object/Bus1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus2", Resources(L"/05_Object/Bus2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus3", Resources(L"/05_Object/Bus3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus4", Resources(L"/05_Object/Bus4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus5", Resources(L"/05_Object/Bus5.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus6", Resources(L"/05_Object/Bus6.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus7", Resources(L"/05_Object/Bus7.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus8", Resources(L"/05_Object/Bus8.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus9", Resources(L"/05_Object/Bus9.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus10", Resources(L"/05_Object/Bus10.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bus11", Resources(L"/05_Object/Bus11.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cabinet1", Resources(L"/05_Object/Cabinet1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cabinet2", Resources(L"/05_Object/Cabinet2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cabinet3", Resources(L"/05_Object/Cabinet3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cabinet4", Resources(L"/05_Object/Cabinet4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cabinet5", Resources(L"/05_Object/Cabinet5.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cabinet6", Resources(L"/05_Object/Cabinet6.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cabinet7", Resources(L"/05_Object/Cabinet7.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cabinet8", Resources(L"/05_Object/Cabinet8.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Car1", Resources(L"/05_Object/Car1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Car2", Resources(L"/05_Object/Car2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Car3", Resources(L"/05_Object/Car3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Car4", Resources(L"/05_Object/Car4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Car5", Resources(L"/05_Object/Car5.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Car6", Resources(L"/05_Object/Car6.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Car7", Resources(L"/05_Object/Car7.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Car8", Resources(L"/05_Object/Car8.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Chair1", Resources(L"/05_Object/Chair1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Chair2", Resources(L"/05_Object/Chair2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Chair3", Resources(L"/05_Object/Chair3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Closet1", Resources(L"/05_Object/Closet1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Closet2", Resources(L"/05_Object/Closet2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Closet3", Resources(L"/05_Object/Closet3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Computer1", Resources(L"/05_Object/Computer1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Computer2", Resources(L"/05_Object/Computer2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Computer3", Resources(L"/05_Object/Computer3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Computer4", Resources(L"/05_Object/Computer4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Computer5", Resources(L"/05_Object/Computer5.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"DeadTree1", Resources(L"/05_Object/DeadTree1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Desk1", Resources(L"/05_Object/Desk1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Desk2", Resources(L"/05_Object/Desk2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Desk3", Resources(L"/05_Object/Desk3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Desk4", Resources(L"/05_Object/Desk4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"dispenser", Resources(L"/05_Object/dispenser.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"dispenser2", Resources(L"/05_Object/dispenser2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"dispenser3", Resources(L"/05_Object/dispenser3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"dispenser4", Resources(L"/05_Object/dispenser4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Doll1", Resources(L"/05_Object/Doll1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Doll2", Resources(L"/05_Object/Doll2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"DustBox1", Resources(L"/05_Object/DustBox1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"DustBox2", Resources(L"/05_Object/DustBox2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"DustBox3", Resources(L"/05_Object/DustBox3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"DustBox4", Resources(L"/05_Object/DustBox4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Fan1", Resources(L"/05_Object/Fan1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Fan2", Resources(L"/05_Object/Fan2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass1", Resources(L"/05_Object/Grass1.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass2", Resources(L"/05_Object/Grass2.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass3", Resources(L"/05_Object/Grass3.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass4", Resources(L"/05_Object/Grass4.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass5", Resources(L"/05_Object/Grass5.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass6", Resources(L"/05_Object/Grass6.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass7", Resources(L"/05_Object/Grass7.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass8", Resources(L"/05_Object/Grass8.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass9", Resources(L"/05_Object/Grass9.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass10", Resources(L"/05_Object/Grass10.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Grass11", Resources(L"/05_Object/Grass11.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"HandWash1", Resources(L"/05_Object/HandWash1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"HandWash2", Resources(L"/05_Object/HandWash2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"MoterCycle1", Resources(L"/05_Object/MoterCycle1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"MoterCycle2", Resources(L"/05_Object/MoterCycle2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"MoterCycle3", Resources(L"/05_Object/MoterCycle3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant1", Resources(L"/05_Object/Plant1.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant2", Resources(L"/05_Object/Plant2.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant3", Resources(L"/05_Object/Plant3.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant4", Resources(L"/05_Object/Plant4.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant5", Resources(L"/05_Object/Plant5.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant6", Resources(L"/05_Object/Plant6.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant7", Resources(L"/05_Object/Plant7.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant7-2", Resources(L"/05_Object/Plant7-2.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant8", Resources(L"/05_Object/Plant8.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant8-2", Resources(L"/05_Object/Plant8-2.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Refrigerator1", Resources(L"/05_Object/Refrigerator1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Rock1", Resources(L"/05_Object/Rock1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Shelf1", Resources(L"/05_Object/Shelf1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Shelf2", Resources(L"/05_Object/Shelf2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Shelf3", Resources(L"/05_Object/Shelf3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Shelf4", Resources(L"/05_Object/Shelf4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Shelf5", Resources(L"/05_Object/Shelf5.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Shelf6", Resources(L"/05_Object/Shelf6.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ShoeCloset1", Resources(L"/05_Object/ShoeCloset1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ShowCase1", Resources(L"/05_Object/ShowCase1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ShowCase2", Resources(L"/05_Object/ShowCase2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ShowCase3", Resources(L"/05_Object/ShowCase3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ShowCase4", Resources(L"/05_Object/ShowCase4.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ShowCase5", Resources(L"/05_Object/ShowCase5.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ShowCase6", Resources(L"/05_Object/ShowCase6.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SignBoard1", Resources(L"/05_Object/SignBoard1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SignBoard2", Resources(L"/05_Object/SignBoard2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SignBoard3", Resources(L"/05_Object/SignBoard3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Sofa1", Resources(L"/05_Object/Sofa1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Sofa2", Resources(L"/05_Object/Sofa2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Sofa3", Resources(L"/05_Object/Sofa3.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Suv", Resources(L"/05_Object/Suv.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Suv2", Resources(L"/05_Object/Suv2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Table1", Resources(L"/05_Object/Table1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Table2", Resources(L"/05_Object/Table2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Toilet1", Resources(L"/05_Object/Toilet1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Toilet2", Resources(L"/05_Object/Toilet2.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ToiletCloset1", Resources(L"/05_Object/ToiletCloset1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tree1", Resources(L"/05_Object/Tree.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tree2", Resources(L"/05_Object/Tree2.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tree3", Resources(L"/05_Object/Tree3.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tree4", Resources(L"/05_Object/Tree4.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tree5", Resources(L"/05_Object/Tree5.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tree6", Resources(L"/05_Object/Tree6.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tree7", Resources(L"/05_Object/Tree7.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tree8", Resources(L"/05_Object/Tree8.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Truck1", Resources(L"/05_Object/Truck1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tv1", Resources(L"/05_Object/Tv1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Washer1", Resources(L"/05_Object/Washer1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"WaterMachine1", Resources(L"/05_Object/WaterMachine1.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"WorkTable1", Resources(L"/05_Object/WorkTable1.png"), 2, 1); });

	//이미지 (Non-Active Object)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Barricade1", Resources(L"/05_Object/Barricade1.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Barricade2", Resources(L"/05_Object/Barricade2.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Barricade3", Resources(L"/05_Object/Barricade3.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Barricade4", Resources(L"/05_Object/Barricade4.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Barricade5", Resources(L"/05_Object/Barricade5.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Barricade6", Resources(L"/05_Object/Barricade6.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Barricade7", Resources(L"/05_Object/Barricade7.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Barricade8", Resources(L"/05_Object/Barricade8.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bollard1", Resources(L"/05_Object/Bollard1.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bollard2", Resources(L"/05_Object/Bollard2.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bollard3", Resources(L"/05_Object/Bollard3.png"), 1, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bollard4", Resources(L"/05_Object/Bollard4.png"), 1, 1); });

	//이미지 (Loading Scene)
	IMAGEMANAGER->LoadFromFile(L"LoadingCat", Resources(L"Cat1.png"), 10, 1);

	mLoadingImage = IMAGEMANAGER->FindImage(L"LoadingCat");
	mLoadingAnimation = new Animation();
	mLoadingAnimation->InitFrameByStartEnd(0, 0, 9, 0, false);
	mLoadingAnimation->SetIsLoop(true);
	mLoadingAnimation->SetFrameUpdateTime(0.1f);
	mLoadingAnimation->Play();
}

void LoadingScene::Release()
{
	SafeDelete(mLoadingAnimation);

}

void LoadingScene::Update()
{
	mLoadingAnimation->Update();
	if (mIsEndLoading == true)
	{
		SceneManager::GetInstance()->LoadScene(L"Scene1");
	}
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
	if (mIsEndLoading == false)
	{
		mLoadingImage->ScaleFrameRender(hdc, (WINSIZEX - mLoadingImage->GetFrameWidth()*5) / 2,
			(WINSIZEY - mLoadingImage->GetFrameHeight()*5) / 2,
			mLoadingAnimation->GetNowFrameX(),
			mLoadingAnimation->GetNowFrameY(),
			mLoadingImage->GetFrameWidth()*5,
			mLoadingImage->GetFrameHeight()*5);
	}
}
