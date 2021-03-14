#include "pch.h"
#include "MapToolBook.h"
#include "Image.h"
#include "Animation.h"
#include "Tile.h"
#include "Button.h"
#include "HousingObject.h"
#define BookSize 2

void MapToolBook::Init()
{
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mImage = ImageManager::GetInstance()->FindImage(L"Book");
	mSizeX = mImage->GetFrameWidth() * BookSize;
	mSizeY = mImage->GetFrameHeight() * BookSize;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mSpeed = 1000.f;

	mAnimation = new Animation();
	mAnimation->InitFrameByStartEnd(0, 0, 8, 4, false);
	mAnimation->SetIsLoop(false);
	mAnimation->SetFrameUpdateTime(0.05f);
	mAnimation->Play();
	mAnimation->SetCallbackFunc([this]()
	{
		//타일 생성
		Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile1");
		int palleteStartX = mRect.left + mSizeX/6;
		int palleteStartY = mRect.top + mSizeY/10;
		mNowTileCountX = tileImage->GetMaxFrameX();
		mNowTileCountY = tileImage->GetMaxFrameY();
		//후에 갯수조정 자동으로 되게 셋팅할 예정
		mPallete.assign(tileImage->GetMaxFrameY(), vector<Tile*>());
		for (int y = 0; y < tileImage->GetMaxFrameY(); ++y)
		{
			for (int x = 0; x < tileImage->GetMaxFrameX(); ++x)
			{
				mPallete[y].push_back(new Tile(
					tileImage,
					palleteStartX + Pallette * x,
					palleteStartY + Pallette * y,
					Pallette,
					Pallette,
					x,
					y,
					x,
					y
				));
				mPallete[y][x]->SetSpeed(mSpeed);
				mPallete[y][x]->SetTileLayer(TileLayer::PalletteType);
			}
		}

		//좌상단 버튼 출력
		mTileButton = new Button(L"BookButton",0,L"Tile", mX - mSizeX / 2+50, mY - 250, 100, 50,
			[this]() {ChangeMode(BookType::Tile); });
		mHouseButton = new Button(L"BookButton", 1, L"House", mX - mSizeX / 2+50, mY - 200, 100, 50,
			[this]() {ChangeMode(BookType::House); });
		mInterectObjectButton = new Button(L"BookButton", 2, L"InterectObject", mX - mSizeX / 2+50, mY - 150, 100, 50,
			[this]() {ChangeMode(BookType::InterectObject); });
		mNoninterectObjectButton = new Button(L"BookButton", 3, L"NoninterectObject", mX - mSizeX / 2+50, mY - 100, 100, 50,
			[this]() {ChangeMode(BookType::NoninterectObject); });

		mNextButton = new Button(L"Next", mX - mSizeX / 6, mY + mSizeY / 3, 50, 50,
			[this]() {
			if (mPage < 15)
			{
				mPage++;
				mIsPageChange = true;
			}
		});
		mPrevButton = new Button(L"Prev", mX - mSizeX / 3, mY + mSizeY / 3, 50, 50,
			[this]() {
			if (mPage > 1)
			{
				mPage--;
				mIsPageChange = true;
			}
		});

		mIsOpenBook = true;
		mPage = 1;
	});


	mIsTypeChange = false;
	mIsOpenBook = false;
	mIsPageChange = false;

	mIsRoofOn = false;
	mRoofBtn = new Button(L"RoofBtn", WINSIZEX / 2 + 200, WINSIZEY / 2 - 100, 100, 100, [this]() {SetIsRoofOn(true); });

}

void MapToolBook::Release()
{
	SafeDelete(mAnimation);

	if (mPallete.size() != NULL)
	{
		for (int y = 0; y < mNowTileCountY; ++y)
		{
			for (int x = 0; x < mNowTileCountX; ++x)
			{
				SafeDelete(mPallete[y][x]);
			}
		}
	}
	SafeDelete(mTileButton);
	SafeDelete(mHouseButton);
	SafeDelete(mInterectObjectButton);
	SafeDelete(mNoninterectObjectButton);
	SafeDelete(mNextButton);
	SafeDelete(mPrevButton);
	SafeDelete(mRoofBtn);
}

void MapToolBook::Update()
{
	//타입별 표시 업데이트
	//이동
	if (Input::GetInstance()->GetKey(VK_LSHIFT))
	{
		if(Input::GetInstance()->GetKey(VK_UP))
		{ 
			//책이동
			mY -= mSpeed * Time::GetInstance()->DeltaTime();
			//버튼 이동
			MoveButtons(0, -mSpeed * Time::GetInstance()->DeltaTime());
			//타일 이동
			if (mPallete.size() != NULL)
			{
				for (int y = 0; y < mNowTileCountY; ++y)
				{
					for (int x = 0; x < mNowTileCountX; ++x)
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
			//버튼 이동
			MoveButtons(0, mSpeed * Time::GetInstance()->DeltaTime());
			if (mPallete.size() != NULL)
			{
				for (int y = 0; y < mNowTileCountY; ++y)
				{
					for (int x = 0; x < mNowTileCountX; ++x)
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
			//버튼 이동
			MoveButtons(mSpeed * Time::GetInstance()->DeltaTime(), 0);
			if (mPallete.size() != NULL)
			{
				for (int y = 0; y < mNowTileCountY; ++y)
				{
					for (int x = 0; x < mNowTileCountX; ++x)
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
			//버튼 이동
			MoveButtons(-mSpeed * Time::GetInstance()->DeltaTime(), 0);
			if (mPallete.size() != NULL)
			{
				for (int y = 0; y < mNowTileCountY; ++y)
				{
					for (int x = 0; x < mNowTileCountX; ++x)
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

	UpdateButtons();
	if (mIsPageChange == true)
	{
		//타일 생성
		Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile"+to_wstring(mPage));
		int palleteStartX = mRect.left + mSizeX / 6;
		int palleteStartY = mRect.top + mSizeY / 10;
		mNowTileCountX = tileImage->GetMaxFrameX();
		mNowTileCountY = tileImage->GetMaxFrameY();
		//리셋
		mPallete.clear();
		
		mPallete.assign(tileImage->GetMaxFrameY(), vector<Tile*>());
		for (int y = 0; y < tileImage->GetMaxFrameY(); ++y)
		{
			for (int x = 0; x < tileImage->GetMaxFrameX(); ++x)
			{
				mPallete[y].push_back(new Tile(
					tileImage,
					palleteStartX + Pallette * x,
					palleteStartY + Pallette * y,
					Pallette,
					Pallette,
					x,
					y,
					x,
					y
				));
				mPallete[y][x]->SetSpeed(mSpeed);
				mPallete[y][x]->SetTileLayer(TileLayer::PalletteType);
			}
		}
		mIsPageChange = false;
	}
}

void MapToolBook::Render(HDC hdc)
{
	RenderRect(hdc, mRect);
	mImage->ScaleFrameRender(hdc, mRect.left, mRect.top,
		mAnimation->GetNowFrameX(),
		mAnimation->GetNowFrameY(),mSizeX,mSizeY);
	
	if (mPallete.size() != NULL)
	{
		for (int y = 0; y < mNowTileCountY; ++y)
		{
			for (int x = 0; x < mNowTileCountX; ++x)
			{
				mPallete[y][x]->Render(hdc);
			}
		}
	}
	
	RenderButtons(hdc);
}

void MapToolBook::MoveButtons(float moveX, float moveY)
{
	if (mTileButton != nullptr)
	{
		mTileButton->Move(mTileButton->GetX() + moveX,
			mTileButton->GetY() + moveY);
	}
	if (mHouseButton != nullptr)
	{
		mHouseButton->Move(mHouseButton->GetX() + moveX,
			mHouseButton->GetY() + moveY);
	}
	if (mInterectObjectButton != nullptr)
	{
		mInterectObjectButton->Move(mInterectObjectButton->GetX() + moveX,
			mInterectObjectButton->GetY() + moveY);
	}
	if (mNoninterectObjectButton != nullptr)
	{
		mNoninterectObjectButton->Move(mNoninterectObjectButton->GetX() + moveX,
			mNoninterectObjectButton->GetY() + moveY);
	}
	if (mNextButton != nullptr)
	{
		mNextButton->Move(mNextButton->GetX() + moveX,
			mNextButton->GetY() + moveY);
	}
	if (mPrevButton != nullptr)
	{
		mPrevButton->Move(mPrevButton->GetX() + moveX,
			mPrevButton->GetY() + moveY);
	}
}

void MapToolBook::UpdateButtons()
{
	if (mTileButton != nullptr)
	{
		mTileButton->Update();
	}
	if (mHouseButton != nullptr)
	{
		mHouseButton->Update();
	}
	if (mInterectObjectButton != nullptr)
	{
		mInterectObjectButton->Update();
	}
	if (mNoninterectObjectButton != nullptr)
	{
		mNoninterectObjectButton->Update();
	}
	if (mNextButton != nullptr)
	{
		mNextButton->Update();
	}
	if (mPrevButton != nullptr)
	{
		mPrevButton->Update();
	}
	if (mRoofBtn != nullptr)
	{
		mRoofBtn->Update();
	}
}

void MapToolBook::RenderButtons(HDC hdc)
{
	if (mTileButton != nullptr)
	{
		mTileButton->Render(hdc);
	}
	if (mHouseButton != nullptr)
	{
		mHouseButton->Render(hdc);
	}
	if (mInterectObjectButton != nullptr)
	{
		mInterectObjectButton->Render(hdc);
	}
	if (mNoninterectObjectButton != nullptr)
	{
		mNoninterectObjectButton->Render(hdc);
	}
	if (mNextButton != nullptr)
	{
		mNextButton->Render(hdc);
	}
	if (mPrevButton != nullptr)
	{
		mPrevButton->Render(hdc);
	}
	if (mRoofBtn != nullptr)
	{
		mRoofBtn->Render(hdc);
	}
}
//버튼 기능
void MapToolBook::ChangeMode(BookType bookType)
{
	if (mBookType != bookType)
	{
		mBookType = bookType;
		mIsTypeChange = true;
	}
	if (mIsTypeChange == true)
	{
		//타일 버튼 클릭시
		if (bookType == BookType::Tile)
		{
			//타버튼 초기화
			mHouseButton->SetIsSelect(false);
			mInterectObjectButton->SetIsSelect(false);
			mNoninterectObjectButton->SetIsSelect(false);
			//페이지교체 불값을 이용하자
			mIsPageChange = true;
		}
		//집버튼 클릭시
		else if (bookType == BookType::House)
		{
			//타버튼 초기화
			mTileButton->SetIsSelect(false);
			mInterectObjectButton->SetIsSelect(false);
			mNoninterectObjectButton->SetIsSelect(false);

			//mHouseObject = new HousingObject("House", 0, 0, SideType::InSide);
			//ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mHouseObject);

			mBookType = bookType;
			mNowTileCountY = 9;
			mNowTileCountX = 9;
			//Image* tempImage;
			Image* tileImage = ImageManager::GetInstance()->FindImage(L"House");
			//Image* tileRoofImage = ImageManager::GetInstance()->FindImage(L"HouseRoof");
			int palleteStartX = mRect.left + 200;
			int palleteStartY = mRect.top + 50;

			mPallete.assign(18, vector<Tile*>());
			for (int y = 0; y < mNowTileCountY; ++y)
			{
				for (int x = 0; x < mNowTileCountX; ++x)
				{

					mPallete[y].push_back(new Tile(
						tileImage,
						palleteStartX + Pallette * x,
						palleteStartY + Pallette * y,
						Pallette,
						Pallette,
						x,
						y,
						x,
						y
					));
					mPallete[y][x]->SetSpeed(mSpeed);
					mPallete[y][x]->SetTileLayer(TileLayer::PalletteType);
				}

			}
		}
		else if (bookType == BookType::InterectObject)
		{
			//타버튼 초기화
			mTileButton->SetIsSelect(false);
			mHouseButton->SetIsSelect(false);
			mNoninterectObjectButton->SetIsSelect(false);
		}
		else if (bookType == BookType::NoninterectObject)
		{
			//타버튼 초기화
			mTileButton->SetIsSelect(false);
			mHouseButton->SetIsSelect(false);
			mInterectObjectButton->SetIsSelect(false);
		}
		mIsTypeChange = false;
	}
}

void MapToolBook::RoofOnMode(int x, int y)
{
	mHouseObject = new HousingObject("Roof", x, y);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mHouseObject);
}


