#include "pch.h"
#include "MapToolBook.h"
#include "Image.h"
#include "Animation.h"
#include "Tile.h"
#include "Button.h"
#include "HousingObject.h"
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
	mAnimation->InitFrameByStartEnd(0, 0, 8, 4, false);
	mAnimation->SetIsLoop(false);
	mAnimation->SetFrameUpdateTime(0.05f);
	mAnimation->Play();
	mAnimation->SetCallbackFunc([this]()
	{
		Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile");
		int palleteStartX = mRect.left + 200;
		int palleteStartY = mRect.top + 50;

		//�Ŀ� �������� �ڵ����� �ǰ� ������ ����
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

	//
	//�»�� ��ư ���
	mTileButton = new Button(L"Tile", mX - mSizeX/2, mY - 300, 200, 50,
		[this]() {ChangeMode(BookType::Tile); });

	mHouseButton = new Button(L"House", mX - mSizeX/2, mY - 250, 200, 50,
		//�Լ� ��������
		//����ü Ÿ���� ������ ����� ���� ���� ���ɼ� �־� ����
		//���ϸ��̼� �з��� �ʿ�
		//����� �߻��Ǵ� ���ٽ�Ȥ�� ���ε�� �־��ٰ�<-�ǵ��� ���ε�� �غ���<-�߰��Լ��� ����� �ٰ�
		//���ٰ� ���ϴ�...
		[this]() {ChangeMode(BookType::House); });
	mInterectObjectButton = new Button(L"InterectObject", mX - mSizeX/2, mY - 200, 200, 50,
		[this]() {ChangeMode(BookType::InterectObject); });
	mNoninterectObjectButton = new Button(L"NoninterectObject", mX - mSizeX/2, mY - 150, 200, 50,
		[this]() {ChangeMode(BookType::NoninterectObject); });

	mIsTypeChange = false;



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
	SafeDelete(mTileButton);
	SafeDelete(mHouseButton);
	SafeDelete(mInterectObjectButton);
	SafeDelete(mNoninterectObjectButton);
}

void MapToolBook::Update()
{
	//Ÿ�Ժ� ǥ�� ������Ʈ
	//�̵�
	if (Input::GetInstance()->GetKey(VK_LSHIFT))
	{
		if(Input::GetInstance()->GetKey(VK_UP))
		{ 
			//å�̵�
			mY -= mSpeed * Time::GetInstance()->DeltaTime();
			//��ư �̵�
			mTileButton->Move(mTileButton->GetX(),
				mTileButton->GetY() - mSpeed * Time::GetInstance()->DeltaTime());
			mHouseButton->Move(mHouseButton->GetX(),
				mHouseButton->GetY() - mSpeed * Time::GetInstance()->DeltaTime());
			mInterectObjectButton->Move(mInterectObjectButton->GetX(),
				mInterectObjectButton->GetY() - mSpeed * Time::GetInstance()->DeltaTime());
			mNoninterectObjectButton->Move(mNoninterectObjectButton->GetX(),
				mNoninterectObjectButton->GetY() - mSpeed * Time::GetInstance()->DeltaTime());
			//Ÿ�� �̵�
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
			//��ư �̵�
			mTileButton->Move(mTileButton->GetX(),
				mTileButton->GetY() + mSpeed * Time::GetInstance()->DeltaTime());
			mHouseButton->Move(mHouseButton->GetX(),
				mHouseButton->GetY() + mSpeed * Time::GetInstance()->DeltaTime());
			mInterectObjectButton->Move(mInterectObjectButton->GetX(),
				mInterectObjectButton->GetY() + mSpeed * Time::GetInstance()->DeltaTime());
			mNoninterectObjectButton->Move(mNoninterectObjectButton->GetX(),
				mNoninterectObjectButton->GetY() + mSpeed * Time::GetInstance()->DeltaTime());
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
			//��ư �̵�
			mTileButton->Move(
				mTileButton->GetX() + mSpeed * Time::GetInstance()->DeltaTime(),
				mTileButton->GetY());
			mHouseButton->Move(
				mHouseButton->GetX() + mSpeed * Time::GetInstance()->DeltaTime(),
				mHouseButton->GetY());
			mInterectObjectButton->Move(
				mInterectObjectButton->GetX() + mSpeed * Time::GetInstance()->DeltaTime(),
				mInterectObjectButton->GetY());
			mNoninterectObjectButton->Move(
				mNoninterectObjectButton->GetX() + mSpeed * Time::GetInstance()->DeltaTime(),
				mNoninterectObjectButton->GetY());
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
			//��ư �̵�
			mTileButton->Move(
				mTileButton->GetX() - mSpeed * Time::GetInstance()->DeltaTime(),
				mTileButton->GetY());
			mHouseButton->Move(
				mHouseButton->GetX() - mSpeed * Time::GetInstance()->DeltaTime(),
				mHouseButton->GetY());
			mInterectObjectButton->Move(
				mInterectObjectButton->GetX() - mSpeed * Time::GetInstance()->DeltaTime(),
				mInterectObjectButton->GetY());
			mNoninterectObjectButton->Move(
				mNoninterectObjectButton->GetX() - mSpeed * Time::GetInstance()->DeltaTime(),
				mNoninterectObjectButton->GetY());
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

	mTileButton->Update();
	mHouseButton->Update();
	mInterectObjectButton->Update();
	mNoninterectObjectButton->Update();

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
	mTileButton->Render(hdc);
	mHouseButton->Render(hdc);
	mInterectObjectButton->Render(hdc);
	mNoninterectObjectButton->Render(hdc);
}

//��ư ���
void MapToolBook::ChangeMode(BookType bookType)
{
	if (mBookType != bookType)
	{
		mBookType = bookType;
		mIsTypeChange = true;
	}
	if (bookType == BookType::House)
	{
		mHouseObject = new HousingObject("House", 0, 0, SideType::InSide);
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mHouseObject);
	}
}