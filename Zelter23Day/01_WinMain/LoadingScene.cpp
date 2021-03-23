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
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Player_run", Resources(L"/03_Player/Player_GunRun.png"), 7, 4); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Player_walk", Resources(L"/03_Player/Player_GunWalk.png"), 7, 4); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Player_attack", Resources(L"/03_Player/Player_attack.png"), 10, 2); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Player_roll", Resources(L"/03_Player/Player_roll.png"), 7, 2); });

	//이미지 (무기 /총)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Weapon_pistol", Resources(L"/03_Player/Weapon_pistol.png"), 1, 1); });
	//이미지 (총알)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bullet", Resources(L"/03_Player/Bullet.png"), 1, 1); });

	//이미지 (이펙트)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"melee_attack", Resources(L"/08_Effect/effect_1.png"), 6, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"pistol_shoot", Resources(L"/08_Effect/effect_2.png"), 7, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"effect_impact", Resources(L"/08_Effect/effect_impact.png"), 8, 7); });

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

	//이미지 (Icon UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Icon_bag", Resources(L"/01_UI/Bag_Btn_Icon.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Icon_tablet", Resources(L"/01_UI/tablet_Icon.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Icon_craft", Resources(L"/01_UI/Craft_Btn_Icon.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Icon_name", Resources(L"/01_UI/icon_name.png"), 3, 1); });
	//이미지 (Keyboard UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Key_C", Resources(L"/01_UI/C-key.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Key_I", Resources(L"/01_UI/I-key.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Key_T", Resources(L"/01_UI/T-key.png")); });

	//이미지 (QuickSlot UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"QuickSlot_ammo", Resources(L"/01_UI/QuickSlot_Ammo.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"QuickSlot_back", Resources(L"/01_UI/QuickSlot_Back.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"QuickSlot_front", Resources(L"/01_UI/QuickSlot_Front.png")); }); 
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"QuickSlot_slotBase", Resources(L"/01_UI/QuickSlot_Slot_Base.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"QuickSlot_tip_close", Resources(L"/01_UI/QuickSlot_Slot_Tip01.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"QuickSlot_tip_open", Resources(L"/01_UI/QuickSlot_Slot_Tip02.png")); });

	//이미지 (Tablet UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Tablet_base", Resources(L"/01_UI/Tablet_Base.png")); });

	//이미지 (인벤토리 UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Inventory_base", Resources(L"/01_UI/Player_InventoryBase.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"Inventory_slot", Resources(L"/01_UI/UI_Slot.png")); });

	//이미지(제작UI)
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"WorkTable", Resources(L"/01_UI/WorkTable.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"WorkTable_start_btn", Resources(L"/01_UI/WorkTable_StartBtn.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"WorkTable_Timer_up", Resources(L"/01_UI/WorkTable_TimerBtn_Down.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->GetInstance()->LoadFromFile(L"WorkTable_Timer_down", Resources(L"/01_UI/WorkTable_TimerBtn_Up.png")); });

	//이미지 (몬스터)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Zombie01", Resources(L"/06_Zombie/zombie01.png"), 5, 6); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Zombie02", Resources(L"/06_Zombie/zombie02.png"), 5, 6); });

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
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"dispenser1", Resources(L"/05_Object/dispenser.png"), 2, 1); });
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
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant5", Resources(L"/05_Object/Plant5.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant6", Resources(L"/05_Object/Plant6.png"), 2, 1); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Plant7", Resources(L"/05_Object/Plant7.png"), 2, 1); });
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
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Suv1", Resources(L"/05_Object/Suv.png"), 2, 1); });
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
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"WaterMachine2", Resources(L"/05_Object/WaterMachine2.png"), 2, 1); });
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

	//이미지 (집)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"House1", Resources(L"/02_House/NewHouse11_Bottom.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"House2", Resources(L"/02_House/NewHouse11_Wall.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"House3", Resources(L"/02_House/NewHouse11_Roof.png")); });
	
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"House4", Resources(L"/02_House/NewHouse22_Bottom.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"House5", Resources(L"/02_House/NewHouse22_Wall.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"House6", Resources(L"/02_House/NewHouse22_Roof.png")); });
	
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"House7", Resources(L"/02_House/NewHouse33_Bottom.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"House8", Resources(L"/02_House/NewHouse33_Wall.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"House9", Resources(L"/02_House/NewHouse33_Roof.png")); });

	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"police1", Resources(L"/02_House/PoliceOffice1_Bottom.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"police2", Resources(L"/02_House/PoliceOffice1_Wall.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"police3", Resources(L"/02_House/PoliceOffice1_Roof.png")); });

	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"shop1", Resources(L"/02_House/Shop11_Bottom.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"shop2", Resources(L"/02_House/Shop11_Wall.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"shop3", Resources(L"/02_House/Shop11_Roof.png")); });

	//이미지 (아이템)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"WoodBrench1", Resources(L"/07_Item/WoodBrench1.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Iron1", Resources(L"/07_Item/Iron1.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Arrow", Resources(L"/07_Item/Arrow.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bandage", Resources(L"/07_Item/Bandage.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"BackPack", Resources(L"/07_Item/BackPack.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Barrigate", Resources(L"/07_Item/Barrigate.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bed", Resources(L"/07_Item/Bed.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Blade", Resources(L"/07_Item/Blade.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"BonFire1", Resources(L"/07_Item/BonFire1.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bottle", Resources(L"/07_Item/Bottle.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Can", Resources(L"/07_Item/Can.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Chair", Resources(L"/07_Item/Chair.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Charcol1", Resources(L"/07_Item/Charcol1.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cloth1", Resources(L"/07_Item/Cloth1.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ClothPiece", Resources(L"/07_Item/ClothPiece.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ClothRag", Resources(L"/07_Item/ClothRag.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ClothWorkTable", Resources(L"/07_Item/ClothWorkTable.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"CookTable", Resources(L"/07_Item/CookTable.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"CrossBag", Resources(L"/07_Item/CrossBag.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"CrossBow", Resources(L"/07_Item/CrossBow.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Crowbar", Resources(L"/07_Item/Crowbar.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Cup", Resources(L"/07_Item/Cup.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"GrilApple", Resources(L"/07_Item/GrilApple.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"GrilMeat1", Resources(L"/07_Item/GrilMeat1.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"GrilStickMeat", Resources(L"/07_Item/GrilStickMeat.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Hats1", Resources(L"/07_Item/Hats1.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Hats2", Resources(L"/07_Item/Hats2.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Hats3", Resources(L"/07_Item/Hats3.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Iron2", Resources(L"/07_Item/Iron2.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"IronAxe", Resources(L"/07_Item/IronAxe.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"IronHammer", Resources(L"/07_Item/IronHammer.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"MetalWorkTable", Resources(L"/07_Item/MetalWorkTable.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Pants1", Resources(L"/07_Item/Pants1.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Pants2", Resources(L"/07_Item/Pants2.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Pipe", Resources(L"/07_Item/Pipe.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Pistol", Resources(L"/07_Item/Pistol.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"PistolBullet", Resources(L"/07_Item/PistolBullet.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"RawApple", Resources(L"/07_Item/RawApple.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"RawMeat", Resources(L"/07_Item/RawMeat.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Rifle", Resources(L"/07_Item/Rifle.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Rifle2", Resources(L"/07_Item/Rifle2.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"RifleBullet", Resources(L"/07_Item/RifleBullet.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Shotgun", Resources(L"/07_Item/Shotgun.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"ShotgunBullet", Resources(L"/07_Item/ShotgunBullet.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SMGBullet", Resources(L"/07_Item/SMGBullet.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"StandTorch", Resources(L"/07_Item/StandTorch.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Steel", Resources(L"/07_Item/Steel.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Stone1", Resources(L"/07_Item/Stone1.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"StoneAxe", Resources(L"/07_Item/StoneAxe.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"StoneHammer", Resources(L"/07_Item/StoneHammer.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"StorageBox", Resources(L"/07_Item/StorageBox.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Tent", Resources(L"/07_Item/Tent.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Torch", Resources(L"/07_Item/Torch.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Uniform", Resources(L"/07_Item/Uniform.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"WaistBag", Resources(L"/07_Item/WaistBag.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"WoodBoard", Resources(L"/07_Item/WoodBoard.png")); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"WoodWorkTable", Resources(L"/07_Item/WoodWorkTable.png")); });

	//사운드
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"BGM", Resources(L"/09_Sound/BGM.mp3"), true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"CrossBowShot", Resources(L"/09_Sound/CrossBowShot.wav"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"ForestSound", Resources(L"/09_Sound/ForestSound.mp3"), true); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"DoorSound", Resources(L"/09_Sound/Door.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"EatSound", Resources(L"/09_Sound/Eat.wav"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"DrinkSound", Resources(L"/09_Sound/EatWater.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"EndingBGM", Resources(L"/09_Sound/EndingBGM.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"PunchSound", Resources(L"/09_Sound/Punch.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"ShotSound", Resources(L"/09_Sound/Shot.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"Siren1", Resources(L"/09_Sound/Siren1.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"Siren2", Resources(L"/09_Sound/Siren2.mp3"), false); });
	AddLoadFunc([]() {SoundPlayer::GetInstance()->LoadFromFile(L"ZombieSound", Resources(L"/09_Sound/Zombie.mp3"), false); });



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
