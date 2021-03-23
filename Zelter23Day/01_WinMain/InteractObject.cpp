#include "pch.h"
#include "InteractObject.h"
#include "Image.h"
#include "Camera.h"
//타일 사이즈 때문에
#include "Tile.h"



InteractObject::InteractObject(const wstring imageKey, float x, float y, int hp, int tileCountX, int tileCountY)
{

	//위치 판정해주기
	mTileIndexX = x/TileSize;
	mTileIndexY = y/TileSize;
	//인풋값 저장
	mInputY = y;
	mHp = hp;
	mImageKey = imageKey;
	mImage = IMAGEMANAGER->FindImage(mImageKey);
	mSizeX = mImage->GetFrameWidth()* InteractObjectSize;
	mSizeY = mImage->GetFrameHeight()* InteractObjectSize;
	mTileCountX = tileCountX;
	mTileCountY = tileCountY;
	if ((mTileCountX * InteractObjectSize) % 2 == 1)//X방향 홀수 타일
	{
		mX = mTileIndexX * TileSize + TileSize / 2 + mTileCountX * InteractObjectSize / 2 * TileSize;
	}
	else if ((mTileCountX * InteractObjectSize) % 2 == 0)//X방향 짝수 타일
	{
		mX = mTileIndexX * TileSize + mTileCountX * InteractObjectSize / 2 * TileSize;// -TileSize / 2;
	}
	mY = mTileIndexY * TileSize - mSizeY / 2 + TileSize/2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	
	int interactRectSizeX, interactRectSizeY;
	if (mTileCountX == 1)
	{
		interactRectSizeX = TileSize / 2;
	}
	else
	{
		interactRectSizeX = TileSize * (mTileCountX * InteractObjectSize - 1);
	}
	if (mTileCountY == 1)
	{
		interactRectSizeY = TileSize / 2;
	}
	else
	{
		interactRectSizeY = TileSize * (mTileCountY * InteractObjectSize - 1);
	}
	mInteractRect = RectMakeCenter(mX, mRect.bottom-TileSize/2*(mTileCountY * InteractObjectSize -1),
		interactRectSizeX, interactRectSizeY);

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

}

void InteractObject::Init()
{	
	mIsInteractive = true;
	mIsInvincible = false;
	mInvincibleCount = 0.f;
	mIndexX = 0;
	mIndexY = 0;
}

void InteractObject::Release()
{
}

void InteractObject::Update()
{
	//피격 판정 딜레이 확인.
	if (mIsInvincible == true)
	{
		mInvincibleCount += Time::GetInstance()->DeltaTime();

		mSizeY -= 20 * Time::GetInstance()->DeltaTime();
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	}
	if (mInvincibleCount > 0.4f && mIsInvincible == true)
	{
		mIsInvincible = false;
		mInvincibleCount = 0.f;
	}
	if (mIsInvincible == false)
	{
		mSizeY = mImage->GetFrameHeight() * InteractObjectSize;
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	}

	if (mImage->GetMaxFrameX()>1&& mHp <= 5)
	{
		mIndexX = 1;
	}
	if (mHp <= 0)
	{
		ItemManager::GetInstance()->randomItem(mImageKey, mX, mY);

		mIsDestroy = true;
	}
}

void InteractObject::Render(HDC hdc)
{
	if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mRect))
	{
		//타일 렉트
		for (int y = 0; y < mTileCountY * InteractObjectSize; ++y)
		{
			for (int x = 0; x < mTileCountX * InteractObjectSize; ++x)
			{
				RECT rc = RectMakeCenter(
					mTileIndexX * TileSize + TileSize / 2 + x * TileSize,
					mRect.bottom - y * TileSize,
					TileSize, TileSize);
				CameraManager::GetInstance()->GetMainCamera()
					->RenderRect(hdc, rc);
			}
		}

		if (Input::GetInstance()->GetKey(VK_LCONTROL))
		{
			//충돌 렉트
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mInteractRect);
			//이미지 렉트
			CameraManager::GetInstance()->GetMainCamera()
				->RenderRect(hdc, mRect);
		}
		//그림자
		CameraManager::GetInstance()->GetMainCamera()
			->ShadowRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY, mSizeX, mSizeY, 0.3f,
				Time::GetInstance()->GetSceneTime()*100);
		//이미지
		CameraManager::GetInstance()->GetMainCamera()
			->ScaleFrameRender(hdc, mImage, mRect.left, mRect.top, mIndexX, mIndexY,mSizeX,mSizeY);
	}
}
