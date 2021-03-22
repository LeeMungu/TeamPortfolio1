#include "pch.h"
#include "Item.h"
#include "Image.h"
#include "Camera.h"
Item::Item(wstring imageKey, float x, float y, int count, ItemKind kind) {
	mKeyName = imageKey;
	mX = x;
	mY = y;
	mCount = count;
	mItemKind = kind;

}
void Item::Init()
{
	
	//keyName에 따라 이미지 정해줌
	if (mKeyName == L"Revolver") {
		mImage = IMAGEMANAGER->FindImage(L"Weapon_pistol");
		mType = ItemType::Weapon;
	}
	else if (mKeyName == L"Apple") {
		mImage = IMAGEMANAGER->FindImage(L"Apple");
		mType = ItemType::Food;
	}
	else if (mKeyName == L"Arrow")
	{
		mImage = IMAGEMANAGER->FindImage(L"Arrow");
		mType = ItemType::Weapon;
	}
	else if (mKeyName == L"BackPack")
	{
		mImage = IMAGEMANAGER->FindImage(L"BackPack");
		mType = ItemType::Equipment;
	}
	else if (mKeyName == L"Bandage")
	{
		mImage = IMAGEMANAGER->FindImage(L"Bandage");
		mType = ItemType::Material;
	}
	else if (mKeyName == L"Barrigate")
	{
		mImage = IMAGEMANAGER->FindImage(L"Barrigate");
		mType = ItemType::structure;
	}
	else if (mKeyName == L"Bed")
	{
		mImage = IMAGEMANAGER->FindImage(L"Bed");
		mType = ItemType::structure;
	}
	else if (mKeyName == L"Blade")
	{
		mImage = IMAGEMANAGER->FindImage(L"Blade");
		mType = ItemType::Weapon;
	}
	else if (mKeyName == L"BonFire1")
	{
		mImage = IMAGEMANAGER->FindImage(L"BonFire1");
		mType = ItemType::structure;
	}
	else if (mKeyName == L"Bottle")
	{
		mImage = IMAGEMANAGER->FindImage(L"Bottle");
		mType = ItemType::Drink;
	}
	else if (mKeyName == L"Can")
	{
		mImage = IMAGEMANAGER->FindImage(L"Can");
		mType = ItemType::Drink;
	}
	else if (mKeyName == L"Chair")
	{
		mImage = IMAGEMANAGER->FindImage(L"Chair");
		mType = ItemType::structure;
	}
	else if (mKeyName == L"Charcol1")
	{
		mImage = IMAGEMANAGER->FindImage(L"Charcol1");
		mType = ItemType::Material;
	}
	else if (mKeyName == L"ClothPiece")
	{
		mImage = IMAGEMANAGER->FindImage(L"ClothPiece");
		mType = ItemType::Material;
	}
	else if (mKeyName == L"ClothRag")
	{
		mImage = IMAGEMANAGER->FindImage(L"ClothRag");
		mType = ItemType::Material;
	}
	else if (mKeyName == L"ClothWorkTable")
	{
		mImage = IMAGEMANAGER->FindImage(L"ClothWorkTable");
		mType = ItemType::structure;
	}
	else if (mKeyName == L"CookTable")
	{
		mImage = IMAGEMANAGER->FindImage(L"CookTable");
		mType = ItemType::structure;
	}
	else if (mKeyName == L"CrossBag")
	{
		mImage = IMAGEMANAGER->FindImage(L"CrossBag");
		mType = ItemType::Equipment;
	}
	else if (mKeyName == L"CrossBow")
	{
		mImage = IMAGEMANAGER->FindImage(L"CrossBow");
		mType = ItemType::Weapon;
	}
	else if (mKeyName == L"CrowBar")
	{
		mImage = IMAGEMANAGER->FindImage(L"CrowBar");
		mType = ItemType::Weapon;
	}
	else if (mKeyName == L"Cup")
	{
		mImage = IMAGEMANAGER->FindImage(L"Cup");
		mType = ItemType::Material;
	}
	else if (mKeyName == L"GrilApple")
	{
		mImage = IMAGEMANAGER->FindImage(L"GrilApple");
		mType = ItemType::Food;
	}
	else if (mKeyName == L"GrilMeat1")
	{
		mImage = IMAGEMANAGER->FindImage(L"GrilMeat1");
		mType = ItemType::Food;
	}
	else if (mKeyName == L"GrilStickMeat")
	{
		mImage = IMAGEMANAGER->FindImage(L"GrilStickMeat");
		mType = ItemType::Food;
	}
	else if (mKeyName == L"Hats1")
	{
		mImage = IMAGEMANAGER->FindImage(L"Hats1");
		mType = ItemType::Equipment;
	}
	else if (mKeyName == L"Hats3")
	{
		mImage = IMAGEMANAGER->FindImage(L"Hats3");
		mType = ItemType::Equipment;
	}
	else if (mKeyName == L"Iron1")
	{
		mImage = IMAGEMANAGER->FindImage(L"Iron1");
		mType = ItemType::Material;
	}
	else if (mKeyName == L"Iron2")
	{
		mImage = IMAGEMANAGER->FindImage(L"Iron2");
		mType = ItemType::Material;
	}
	else if (mKeyName == L"IronAxe")
	{
		mImage = IMAGEMANAGER->FindImage(L"IronAxe");
		mType = ItemType::Weapon;
	}
	else if (mKeyName == L"IronHammer")
	{
	mImage = IMAGEMANAGER->FindImage(L"IronHammer");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"Cloth1")
	{
	mImage = IMAGEMANAGER->FindImage(L"Cloth1");
	mType = ItemType::Equipment;
	}
	else if (mKeyName == L"MetalWorkTable")
	{
	mImage = IMAGEMANAGER->FindImage(L"MetalWorkTable");
	mType = ItemType::structure;
	}
	else if (mKeyName == L"Pants1")
	{
	mImage = IMAGEMANAGER->FindImage(L"Pants1");
	mType = ItemType::Equipment;
	}
	else if (mKeyName == L"Pants2")
	{
	mImage = IMAGEMANAGER->FindImage(L"Pants2");
	mType = ItemType::Equipment;
	}
	else if (mKeyName == L"Pipe")
	{
	mImage = IMAGEMANAGER->FindImage(L"Pipe");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"PistolBullet")
	{
	mImage = IMAGEMANAGER->FindImage(L"PistolBullet");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"RawApple")
	{
	mImage = IMAGEMANAGER->FindImage(L"RawApple");
	mType = ItemType::Food;
	}
	else if (mKeyName == L"RawMeat")
	{
	mImage = IMAGEMANAGER->FindImage(L"RawMeat");
	mType = ItemType::Food;
	}
	else if (mKeyName == L"Rifle")
	{
	mImage = IMAGEMANAGER->FindImage(L"Rifle");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"Rifle2")
	{
	mImage = IMAGEMANAGER->FindImage(L"Rifle2");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"RifleBullet")
	{
	mImage = IMAGEMANAGER->FindImage(L"RifleBullet");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"Shotgun")
	{
	mImage = IMAGEMANAGER->FindImage(L"Shotgun");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"ShotgunBullet")
	{
	mImage = IMAGEMANAGER->FindImage(L"ShotgunBullet");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"SMGBullet")
	{
	mImage = IMAGEMANAGER->FindImage(L"SMGBullet");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"StandTorch")
	{
	mImage = IMAGEMANAGER->FindImage(L"StandTorch");
	mType = ItemType::structure;
	}
	else if (mKeyName == L"Steel")
	{
	mImage = IMAGEMANAGER->FindImage(L"Steel");
	mType = ItemType::Material;
	}
	else if (mKeyName == L"Stone1")
	{
	mImage = IMAGEMANAGER->FindImage(L"Stone1");
	mType = ItemType::Material;
	}
	else if (mKeyName == L"StoneAxe")
	{
	mImage = IMAGEMANAGER->FindImage(L"StoneAxe");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"StoneHammer")
	{
	mImage = IMAGEMANAGER->FindImage(L"StoneHammer");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"StorageBox")
	{
	mImage = IMAGEMANAGER->FindImage(L"StorageBox");
	mType = ItemType::structure;
	}
	else if (mKeyName == L"Tent")
	{
	mImage = IMAGEMANAGER->FindImage(L"Tent");
	mType = ItemType::structure;
	}
	else if (mKeyName == L"Torch")
	{
	mImage = IMAGEMANAGER->FindImage(L"Torch");
	mType = ItemType::Weapon;
	}
	else if (mKeyName == L"Uniform")
	{
	mImage = IMAGEMANAGER->FindImage(L"Uniform");
	mType = ItemType::Equipment;
	}
	else if (mKeyName == L"WaistBag")
	{
	mImage = IMAGEMANAGER->FindImage(L"WaistBag");
	mType = ItemType::Equipment;
	}
	else if (mKeyName == L"WoodBoard")
	{
	mImage = IMAGEMANAGER->FindImage(L"WoodBoard");
	mType = ItemType::structure;
	}
	else if (mKeyName == L"WoodBrench1")
	{
	mImage = IMAGEMANAGER->FindImage(L"WoodBrench1");
	mType = ItemType::Material;
	}
	else if (mKeyName == L"WoodWorkTable")
	{
	mImage = IMAGEMANAGER->FindImage(L"WoodWorkTable");
	mType = ItemType::structure;
	}
	
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Item::Release() {
}

void Item::Update()
{
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Item::Render(HDC hdc)
{
	if (mItemKind == ItemKind::drop) {
		CameraManager::GetInstance()->GetMainCamera()->
			Render(hdc, mImage, mRect.left, mRect.top);
	}
	else {
		mImage->Render(hdc, mRect.left, mRect.top);
		
		wstring strSceneTime = to_wstring(mCount);
		D2DRenderer::GetInstance()
			->RenderText(mX, mY, strSceneTime.c_str(), 10);
	}

	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, mRect);
	}
}