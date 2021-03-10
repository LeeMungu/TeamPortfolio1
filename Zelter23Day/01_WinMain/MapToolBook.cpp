#include "pch.h"
#include "MapToolBook.h"
#include "Image.h"
#include "Animation.h"
#include "Tile.h"
#include "Button.h"

void MapToolBook::Init()
{
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mImage = ImageManager::GetInstance()->FindImage(L"Book");
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mSpeed = 1000.f;

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0,0,8,4,false);
	mAnimation->SetIsLoop(false);
	mAnimation->SetFrameUpdateTime(0.05f);
	mAnimation->Play();
	mAnimation->SetCallbackFunc([this]()
	{
		Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile");
		int palleteStartX = mRect.left+200;
		int palleteStartY = mRect.top+50;

		//후에 갯수조정 자동으로 되게 셋팅할 예정
		mPallete.assign(4, vector<Tile*>());
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				mPallete[y].push_back(new Tile(
					tileImage,
					palleteStartX + Pallette * x,
					palleteStartY + Pallette * y,
					Pallette,
					Pallette,
					x,
					y
				));
				mPallete[y][x]->SetSpeed(mSpeed);
				mPallete[y][x]->SetTileLayer(TileLayer::PalletteType);
			}
		}
	});

}

void MapToolBook::Release()
{
	SafeDelete(mAnimation);
	if (mPallete.size() != NULL)
	{
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				SafeDelete(mPallete[y][x]);
			}
		}
	}
}

void MapToolBook::Update()
{
	if (Input::GetInstance()->GetKey(VK_LSHIFT))
	{
		if(Input::GetInstance()->GetKey(VK_UP))
		{ 
			mY -= mSpeed * Time::GetInstance()->DeltaTime();
			if (mPallete.size() != NULL)
			{
				for (int y = 0; y < 4; ++y)
				{
					for (int x = 0; x < 8; ++x)
					{
						mPallete[y][x]->Move(
							mPallete[y][x]->GetX(), 
							mPallete[y][x]->GetY() - mSpeed * Time::GetInstance()->DeltaTime());
					}
				}
			}
		}
		if (Input::GetInstance()->GetKey(VK_DOWN))
		{
			mY += mSpeed * Time::GetInstance()->DeltaTime();
			if (mPallete.size() != NULL)
			{
				for (int y = 0; y < 4; ++y)
				{
					for (int x = 0; x < 8; ++x)
					{
						mPallete[y][x]->Move(
							mPallete[y][x]->GetX(),
							mPallete[y][x]->GetY() + mSpeed * Time::GetInstance()->DeltaTime());
					}
				}
			}
		}
		if (Input::GetInstance()->GetKey(VK_RIGHT))
		{
			mX += mSpeed * Time::GetInstance()->DeltaTime();
			if (mPallete.size() != NULL)
			{
				for (int y = 0; y < 4; ++y)
				{
					for (int x = 0; x < 8; ++x)
					{
						mPallete[y][x]->Move(
							mPallete[y][x]->GetX() + mSpeed * Time::GetInstance()->DeltaTime(),
							mPallete[y][x]->GetY() );
					}
				}
			}
		}
		if (Input::GetInstance()->GetKey(VK_LEFT))
		{
			mX -= mSpeed * Time::GetInstance()->DeltaTime();
			if (mPallete.size() != NULL)
			{
				for (int y = 0; y < 4; ++y)
				{
					for (int x = 0; x < 8; ++x)
					{
						mPallete[y][x]->Move(
							mPallete[y][x]->GetX() - mSpeed * Time::GetInstance()->DeltaTime(),
							mPallete[y][x]->GetY());
					}
				}
			}
		}
	}
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mAnimation->Update();

}

void MapToolBook::Render(HDC hdc)
{
	mImage->FrameRender(hdc, mRect.left, mRect.top,
		mAnimation->GetNowFrameX(),
		mAnimation->GetNowFrameY());
	
	if (mPallete.size() != NULL)
	{
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				mPallete[y][x]->Render(hdc);
			}
		}
	}
}