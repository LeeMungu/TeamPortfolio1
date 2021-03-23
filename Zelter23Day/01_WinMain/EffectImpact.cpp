#include "pch.h"
#include "EffectImpact.h"
#include "Image.h"
#include "Camera.h"
#include "Animation.h"


#define effectscale 2
EffectImpact::EffectImpact(wstring imagekey, int x, int y, int indexX)
{
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, this);
	mImage = IMAGEMANAGER->GetInstance()->FindImage(L"effect_impact");
	mImageKey = imagekey;
	mX = x;
	mY = y;	
	mSizeX = mImage->GetFrameWidth() * effectscale;
	mSizeY = mImage->GetFrameHeight() * effectscale;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mIndexX = indexX;
	mIndexY ;
	mAngle = Random::GetInstance()->RandomInt(70, 240) * 0.01f;
	mSpeed = Random::GetInstance()->RandomInt(100, 130);
	mGravity = 150.f;

	vector<GameObject*> tempObject = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);
	if (tempObject.size() != NULL)
	{
		for (int i = 0; i < tempObject.size(); ++i)
		{
			mInteractObject = (InteractObject*)tempObject[i];

		}
	}
	Init();
}

void EffectImpact::Init()
{
	mObjectLayerList.insert(make_pair(L"Bench1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Bench2", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Bus1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus3", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus4", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus5", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus6", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus7", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus8", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus9", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus10", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Bus11", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Cabinet1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Cabinet2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Cabinet3", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Cabinet4", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Cabinet5", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Cabinet6", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Cabinet7", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Cabinet8", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Car1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Car2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Car3", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Car4", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Car5", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Car6", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Car7", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Car8", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Chair1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Chair2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Chair3", TypeLayer::Leather));
	mObjectLayerList.insert(make_pair(L"Closet1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Closet2", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Closet3", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Computer1", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"Computer2", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"Computer3", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"Computer4", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"Computer5", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"DeadTree1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Desk1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Desk2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Desk3", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Desk4", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"dispenser", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"dispenser2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"dispenser3", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"dispenser4", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Doll1", TypeLayer::fabric));
	mObjectLayerList.insert(make_pair(L"Doll2", TypeLayer::fabric));
	mObjectLayerList.insert(make_pair(L"DustBox1", TypeLayer::plastic));
	mObjectLayerList.insert(make_pair(L"DustBox2", TypeLayer::plastic));
	mObjectLayerList.insert(make_pair(L"DustBox3", TypeLayer::plastic));
	mObjectLayerList.insert(make_pair(L"DustBox4", TypeLayer::plastic));
	mObjectLayerList.insert(make_pair(L"Fan1", TypeLayer::plastic));
	mObjectLayerList.insert(make_pair(L"Fan2", TypeLayer::plastic));
	mObjectLayerList.insert(make_pair(L"HandWash1", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"HandWash2", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"MoterCycle1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"MoterCycle2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"MoterCycle3", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Plant1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Plant2", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Plant3", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Plant4", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Plant5", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Plant6", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Plant7", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Refrigerator1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Rock1", TypeLayer::stone));
	mObjectLayerList.insert(make_pair(L"Shelf1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Shelf2", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Shelf3", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Shelf4", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Shelf5", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Shelf6", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"ShoeCloset1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"ShowCase1", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"ShowCase2", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"ShowCase3", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"ShowCase4", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"ShowCase5", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"ShowCase6", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"SignBoard1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"SignBoard2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"SignBoard3", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Sofa1", TypeLayer::Leather));
	mObjectLayerList.insert(make_pair(L"Sofa2", TypeLayer::Leather));
	mObjectLayerList.insert(make_pair(L"Sofa3", TypeLayer::Leather));
	mObjectLayerList.insert(make_pair(L"Suv1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Suv2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Table1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Table2", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Toilet1", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"Toilet2", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"ToiletCloset1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Tree1", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Tree2", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Tree3", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Tree4", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Tree5", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Tree6", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Tree7", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Tree8", TypeLayer::wood));
	mObjectLayerList.insert(make_pair(L"Truck1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Tv1", TypeLayer::glass));
	mObjectLayerList.insert(make_pair(L"Washer1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"WaterMachine1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"WaterMachine2", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"WorkTable1", TypeLayer::Iron));
	mObjectLayerList.insert(make_pair(L"Zombie01", TypeLayer::fabric));
	mObjectLayerList.insert(make_pair(L"Zombie02", TypeLayer::fabric));
}

void EffectImpact::Release()
{
}

void EffectImpact::Update()
{
	mX += cosf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mY -= sinf(mAngle) * mSpeed * Time::GetInstance()->DeltaTime();
	mSpeed -= mGravity * Time::GetInstance()->DeltaTime();
	if (mSpeed <= 0)
	{
		mIsDestroy = true;
	}



	if (mObjectLayerList.size() != NULL)
	{
		if (mObjectLayerList.find(mImageKey)->second == TypeLayer::stone)
		{
			mIndexY = 0;
		}
		else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::wood)
		{
			mIndexY = 1;
		}
		else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::glass)
		{
			mIndexY = 2;
		}
		else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::fabric)
		{
			mIndexY = 3;
		}
		else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::Iron)
		{
			mIndexY = 4;
		}
		else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::Leather)
		{
			mIndexY = 5;
		}
		else if (mObjectLayerList.find(mImageKey)->second == TypeLayer::plastic)
		{
			mIndexY = 6;
		}
	}



}

void EffectImpact::Render(HDC hdc)
{
	//CameraManager::GetInstance()->GetMainCamera()->Render(hdc, mImage, mX, mY, mIndexX, mIndexY, mSizeX, mSizeY);

	CameraManager::GetInstance()->GetMainCamera()->FrameRender(hdc, mImage, mX, mY, mIndexX, mIndexY);
}
