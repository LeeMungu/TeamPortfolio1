#include "pch.h"
#include "MapToolBook.h"
#include "Image.h"
#include "Animation.h"
#include "Tile.h"
#include "Button.h"
#include "HousingObject.h"
#include "ObjectButton.h"
#include "Mouse.h"
#define BookSize 2

void MapToolBook::Init()
{

	IMAGEMANAGER->GetInstance()->LoadFromFile(L"NextPageButton", Resources(L"/01_UI/NextPageButton.png"));
	IMAGEMANAGER->GetInstance()->LoadFromFile(L"PrevPageButton", Resources(L"/01_UI/PrevPageButton.png"));

	mX = WINSIZEX;
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
		//Ÿ�� ����
		Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile1");
		int palleteStartX = mRect.left + mSizeX/6;
		int palleteStartY = mRect.top + mSizeY/10;
		mNowTileCountX = tileImage->GetMaxFrameX();
		mNowTileCountY = tileImage->GetMaxFrameY();
		//�Ŀ� �������� �ڵ����� �ǰ� ������ ����
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

		//�»�� ��ư ���
		mTileButton = new Button(L"BookButton",0,L"Tile", mX - mSizeX / 2+50, mY - 250, 100, 50,
			[this]() {ChangeMode(BookType::Tile); });
		mHouseButton = new Button(L"BookButton", 1, L"House", mX - mSizeX / 2+50, mY - 200, 100, 50,
			[this]() {ChangeMode(BookType::House); });
		mInterectObjectButton = new Button(L"BookButton", 2, L"InterectObject", mX - mSizeX / 2+50, mY - 150, 100, 50,
			[this]() {ChangeMode(BookType::InterectObject); });
		mNoninterectObjectButton = new Button(L"BookButton", 3, L"NoninterectObject", mX - mSizeX / 2+50, mY - 100, 100, 50,
			[this]() {ChangeMode(BookType::NoninterectObject); });

		mNextButton = new Button(L"NextPageButton", mX - mSizeX / 6, mY + mSizeY / 3, 1.f,
			[this]() {
			if (mBookType == BookType::Tile)
			{
				if (mPage < 16)
				{
					mPage++;
					mIsPageChange = true;
				}
			}
			else if (mBookType == BookType::InterectObject)
			{
				if (mPage < 15)
				{
					mPage++;
					mIsPageChange = true;
				}
			}
			else if (mBookType == BookType::House)
			{
				if (mPage < 15)
				{
					mPage++;
					mIsPageChange = true;
				}
			}
		});
		mPrevButton = new Button(L"PrevPageButton", mX - mSizeX / 3.5, mY + mSizeY / 3, 1.f,
			[this]() {
			if (mBookType == BookType::Tile)
			{
				if (mPage > 1)
				{
					mPage--;
					mIsPageChange = true;
				}
			}
			else if (mBookType == BookType::InterectObject)
			{
				if (mPage > 1)
				{
					mPage--;
					mIsPageChange = true;
				}
			}
			else if (mBookType == BookType::House)
			{
				if (mPage > 1)
				{
					mPage--;
					mIsPageChange = true;
				}
			}
		});

		mIsOpenBook = true;
		mPage = 1;
	});


	mIsTypeChange = false;
	mIsOpenBook = false;
	mIsPageChange = false;


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

	
	//������Ʈ�޴��� �ʱ�ȭ
	ObjectManager::GetInstance()->Release();
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
			MoveButtons(0, -mSpeed * Time::GetInstance()->DeltaTime());
			//Ÿ�� �̵�
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
			//��ư �̵�
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
			//��ư �̵�
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
			//��ư �̵�
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

	//��ư�� ������Ʈ
	UpdateButtons();
	//������ �ѱ涧
	if (mIsPageChange == true)
	{
		if (mBookType == BookType::Tile)
		{
			//Ÿ�� ����
			Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile" + to_wstring(mPage));
			int palleteStartX = mRect.left + mSizeX / 6;
			int palleteStartY = mRect.top + mSizeY / 10;
			mNowTileCountX = tileImage->GetMaxFrameX();
			mNowTileCountY = tileImage->GetMaxFrameY();
			//����
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
		}
		if (mBookType == BookType::InterectObject)
		{
			if (mPage == 1)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				//������Ʈ��ư ����
				for (int i = 0; i < 8; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Tree" + to_wstring(i + 1), mX - 250 + 100 * (i % 3), mY - 210 + 145 * (i / 3), [i]() {
						Mouse* mouse = new Mouse(L"Tree" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 2)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				//������Ʈ��ư ����
				for (int i = 0; i < 8; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Cabinet" + to_wstring(i + 1), mX - 250 + 100 * (i % 3), mY - 210 + 145 * (i / 3), [i]() {
						Mouse* mouse = new Mouse(L"Cabinet" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 3)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				//������Ʈ��ư ����
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Chair" + to_wstring(i + 1), mX - 250 + 100 * (i % 3), mY - 210 + 145 * (i / 3), [i]() {
						Mouse* mouse = new Mouse(L"Chair" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Closet" + to_wstring(i + 1), mX - 250 + 100 * ((i+3) % 3), mY - 210 + 145 * ((i+3) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Closet" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if(i>=2)
						{ 
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 2; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Bench" + to_wstring(i + 1), mX - 250 + 100 * ((i + 6) % 3), mY - 210 + 145 * ((i + 6) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Bench" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 1)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}

			}
			else if (mPage == 4)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				//������Ʈ��ư ����
				for (int i = 0; i < 5; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Computer" + to_wstring(i + 1), mX - 250 + 100 * (i % 3), mY - 210 + 145 * (i / 3), [i]() {
						Mouse* mouse = new Mouse(L"Computer" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 4)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 4; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Desk" + to_wstring(i + 1), mX - 250 + 100 * ((i + 5)% 3), mY - 210 + 145 * ((i + 5)/ 3), [i]() {
						Mouse* mouse = new Mouse(L"Desk" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 2)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 5)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 2; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Doll" + to_wstring(i + 1), 
						mX - 250 + 100 * (i % 3), mY - 210 + 145 * (i / 3), [i]() {
						Mouse* mouse = new Mouse(L"Doll" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 4; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"DustBox" + to_wstring(i + 1),
						mX - 250 + 100 * ((i+2) % 3), mY - 210 + 145 * ((i+2) / 3), [i]() {
						Mouse* mouse = new Mouse(L"DustBox" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 3)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else if(i>=2)
						{
							mouse->SetTileCountX(3);
							mouse->SetTileCountY(1);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 2; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Fan" + to_wstring(i + 1),
						mX - 250 + 100 * ((i + 6) % 3), mY - 210 + 145 * ((i + 6) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Fan" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 6)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Bus" + to_wstring(i + 1),
						mX - 250 + 100 * (i % 3), mY - 110 + 145 * (i / 3), [i]() {
						Mouse* mouse = new Mouse(L"Bus" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(3);
						mouse->SetTileCountY(8);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Car" + to_wstring(i + 5 + 1),
						mX - 250 + 100 * ((i) % 3), mY + 100 + 145 * ((i) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Car" + to_wstring(i + 5 + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(4);
						mouse->SetTileCountY(2);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 7)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Bus" + to_wstring(i + 6 + 1),
						mX - 250 + 100, mY - 170 + 120 * (i % 3), [i]() {
						Mouse* mouse = new Mouse(L"Bus" + to_wstring(i + 6 + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(9);
						mouse->SetTileCountY(3);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 8)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 2; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Bus" + to_wstring(i + 9 + 1),
						mX - 250 + 100, mY - 170 + 120 * (i % 3), [i]() {
						Mouse* mouse = new Mouse(L"Bus" + to_wstring(i + 9 + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(9);
						mouse->SetTileCountY(3);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 5; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Car" + to_wstring(i + 1),
						mX - 280 + 60*(i % 5), mY - 170 + 120 * 2, [i]() {
						Mouse* mouse = new Mouse(L"Car" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(2);
						mouse->SetTileCountY(3);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 9)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 2; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Suv" + to_wstring(i+ 1),
						mX - 250 + 100 * ((i) % 3), mY - 170 + 120 * ((i) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Suv" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 1)
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(4);
						}
						else
						{
							mouse->SetTileCountX(4);
							mouse->SetTileCountY(2);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 2; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"HandWash" + to_wstring(i + 1),
						mX - 250 + 100 * ((i+2) % 3), mY - 170 + 120 * ((i+2) / 3), [i]() {
						Mouse* mouse = new Mouse(L"HandWash" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"MoterCycle" + to_wstring(i + 1),
						mX - 250 + 100 * ((i + 4) % 3), mY - 170 + 120 * ((i + 4) / 3), [i]() {
						Mouse* mouse = new Mouse(L"MoterCycle" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if(i >= 1)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 1; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Refrigerator" + to_wstring(i + 1),
						mX - 250 + 100 * ((i + 8) % 3), mY - 210 + 145 * ((i + 8) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Refrigerator" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 10)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Plant" + to_wstring(i + 5),
						mX - 250 + 100 * (i % 3), mY - 210 + 145 * (i / 3), [i]() {
						Mouse* mouse = new Mouse(L"Plant" + to_wstring(i + 5), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				
				for (int i = 0; i < 6; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Shelf" + to_wstring(i + 1),
						mX - 250 + 100 * ((i + 3) % 3), mY - 210 + 145 * ((i + 3) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Shelf" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 5)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 11)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 6; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"ShowCase" + to_wstring(i + 1),
						mX - 250 + 100 * ((i) % 3), mY - 210 + 145 * ((i) / 3), [i]() {
						Mouse* mouse = new Mouse(L"ShowCase" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 5)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Sofa" + to_wstring(i + 1),
						mX - 250 + 100 * ((i+6) % 3), mY - 210 + 145 * ((i+6) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Sofa" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 2)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(3);
						}
						else if (i >= 1)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(3);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 12)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 2; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Table" + to_wstring(i + 1),
						mX - 250 + 100 * ((i) % 3), mY - 210 + 145 * ((i) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Table" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 1)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(3);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 1; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Washer" + to_wstring(i + 1),
						mX - 250 + 100 * ((i+2) % 3), mY - 210 + 145 * ((i+2) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Washer" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 2; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"WaterMachine" + to_wstring(i + 1),
						mX - 250 + 100 * ((i + 3) % 3), mY - 210 + 145 * ((i + 3) / 3), [i]() {
						Mouse* mouse = new Mouse(L"WaterMachine" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 2; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Toilet" + to_wstring(i + 1),
						mX - 250 + 100 * ((i + 5) % 3), mY - 210 + 145 * ((i + 5) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Toilet" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(1);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 13)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Barricade" + to_wstring(i + 1),
						mX - 250 + 100 * ((i) % 3), mY - 210+30 + 145 * ((i) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Barricade" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i == 0)
						{
							mouse->SetTileCountX(3);
							mouse->SetTileCountY(4);
						}
						else if(i == 1)
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(5);
						}
						else if (i == 2)
						{
							mouse->SetTileCountX(4);
							mouse->SetTileCountY(5);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 3; i < 4; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Barricade" + to_wstring(i + 1),
						mX - 250 +100+ 100 * ((i) % 3), mY - 210 + 170 * ((i) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Barricade" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i == 3)
						{
							mouse->SetTileCountX(11);
							mouse->SetTileCountY(2);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 4; i < 8; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Barricade" + to_wstring(i + 1),
						mX - 250 + 75 * ((i) % 4), mY - 210 + 145 * 2, [i]() {
						Mouse* mouse = new Mouse(L"Barricade" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 6)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(2);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 14)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 4; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Bollard" + to_wstring(i + 1),
						mX - 250 + 100 * ((i) % 3), mY - 210 + 110 * ((i) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Bollard" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 2)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(1);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 3; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"SignBoard" + to_wstring(i + 1),
						mX - 250 + 100 * ((i+4) % 3), mY - 210 + 110 * ((i+4) / 3), [i]() {
						Mouse* mouse = new Mouse(L"SignBoard" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 1)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(1);
						}
						else
						{
							mouse->SetTileCountX(2);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
				for (int i = 0; i < 4; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"dispenser" + to_wstring(i + 1),
						mX - 250 + 75 * ((i)), mY - 210 + 145 * 2, [i]() {
						Mouse* mouse = new Mouse(L"dispenser" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						if (i >= 2)
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(1);
						}
						else
						{
							mouse->SetTileCountX(1);
							mouse->SetTileCountY(1);
						}
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
			else if (mPage == 15)
			{
				//������Ʈ��ư �ʱ�ȭ
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
				for (int i = 0; i < 4; ++i)
				{
					ObjectButton* objectButton = new ObjectButton(L"Door" + to_wstring(i + 1),
						mX - 250 + 100 * ((i) % 3), mY - 210 + 110 * ((i) / 3), [i]() {
						Mouse* mouse = new Mouse(L"Door" + to_wstring(i + 1), ObjectLayer::InteractObject);
						mouse->SetHpMax(10);
						mouse->SetTileCountX(2);
						mouse->SetTileCountY(1);
						mouse->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
					objectButton->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				}
			}
		}
		if (mBookType == BookType::House)
		{
			if (mPage == 1)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
			
				ObjectButton* objectButton = new ObjectButton(L"House3", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House3", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
			}
			if (mPage == 2)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
			
				ObjectButton* objectButton = new ObjectButton(L"House2", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House2", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
				
			}
			if (mPage == 3)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}
			
				ObjectButton* objectButton = new ObjectButton(L"House1", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House1", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
			
			}
			if (mPage == 4)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"House4", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House4", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 5)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"House5", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House5", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 6)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"House6", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House6", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 7)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"House7", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House7", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 8)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"House8", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House8", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 9)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"House9", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House9", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 10)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"police1", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"police1", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 11)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"police2", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"police2", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 12)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"police3", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"police3", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 13)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"shop1", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"shop1", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 14)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"shop2", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"shop2", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}
			if (mPage == 15)
			{
				vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
				if (tempButton.size() != NULL)
				{
					for (int i = 0; i < tempButton.size(); ++i)
					{
						tempButton[i]->SetIsDestroy(true);
					}
				}

				ObjectButton* objectButton = new ObjectButton(L"shop3", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"shop3", ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);

			}



		}

		mIsPageChange = false;
	}
	//å���� ��ư�� ������Ʈ
	//if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton).size() != NULL)
	//{
	//	ObjectManager::GetInstance()->Update();
	//}
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

	//vector<GameObject*>objectButtonList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
	//if (objectButtonList.size() != NULL)
	//{
	//	ObjectManager::GetInstance()->Render(hdc);
	//}
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
	vector<GameObject*>objectButtonList =  ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
	if (objectButtonList.size() != NULL)
	{
		for (int i = 0; i < objectButtonList.size(); ++i)
		{
			ObjectButton* tempObjectButton = ((ObjectButton*)objectButtonList[i]);
			
			tempObjectButton->Move(
				tempObjectButton->GetX() + moveX,
				tempObjectButton->GetY() + moveY);
		}
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
}
//��ư ���
void MapToolBook::ChangeMode(BookType bookType)
{
	//���콺 �ʱ�ȭ<-�Ӽ�������� ü�����ϸ� ���콺 �ʱ�ȭ�ϵ���
	vector<GameObject*> tempMouse = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Mouse);
	if (tempMouse.size() != NULL)
	{
		for (int i = 0; i < tempMouse.size(); ++i)
		{
			tempMouse[i]->SetIsDestroy(true);
		}
	}
	//��Ÿ�� �����ֱ�
	if (mBookType != bookType)
	{
		mBookType = bookType;
		mIsTypeChange = true;
	}
	if (mIsTypeChange == true)
	{
		//Ÿ�� ��ư Ŭ����
		if (bookType == BookType::Tile)
		{
			//Ÿ��ư �ʱ�ȭ
			mHouseButton->SetIsSelect(false);
			mInterectObjectButton->SetIsSelect(false);
			mNoninterectObjectButton->SetIsSelect(false);

			//������Ʈ��ư �ʱ�ȭ
			vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
			if (tempButton.size() != NULL)
			{
				for (int i = 0; i < tempButton.size(); ++i)
				{
					tempButton[i]->SetIsDestroy(true);
				}
			}
			//��������ü �Ұ��� �̿�����
			mIsPageChange = true;
		}
		//����ư Ŭ����
		else if (bookType == BookType::House)
		{
			//Ÿ��ư �ʱ�ȭ
			mTileButton->SetIsSelect(false);
			mInterectObjectButton->SetIsSelect(false);
			mNoninterectObjectButton->SetIsSelect(false);

			mPallete.clear();

			//������Ʈ��ư �ʱ�ȭ
			vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
			if (tempButton.size() != NULL)
			{
				for (int i = 0; i < tempButton.size(); ++i)
				{
					tempButton[i]->SetIsDestroy(true);
				}
			}
			//mHouseObject = new HousingObject("House", 0, 0, SideType::InSide);
			//ObjectManager::GetInstance()->AddObject(ObjectLayer::Tile, mHouseObject);

				mPage = 1;
				ObjectButton* objectButton = new ObjectButton(L"House3", mX - 250 + 100, mY - 210 + 145, []() {
					Mouse* mouse = new Mouse(L"House3" , ObjectLayer::HousingObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
					});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
			
		}
		else if (bookType == BookType::InterectObject)
		{
			//Ÿ��ư �ʱ�ȭ
			mTileButton->SetIsSelect(false);
			mHouseButton->SetIsSelect(false);
			mNoninterectObjectButton->SetIsSelect(false);
			//�ȷ�Ʈ �ʱ�ȭ
			mPallete.clear();
			//������Ʈ��ư �ʱ�ȭ
			vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
			if (tempButton.size() != NULL)
			{
				for (int i = 0; i < tempButton.size(); ++i)
				{
					tempButton[i]->SetIsDestroy(true);
				}
			}
			//������ �ʱ�ȭ
			mPage = 1;
			//������Ʈ��ư ����
			for (int i = 0; i < 8; ++i)
			{
				ObjectButton* objectButton = new ObjectButton(L"Tree"+to_wstring(i+1), mX - 250 +100*(i%3), mY - 210+145*(i/3), [i]() {
					Mouse* mouse = new Mouse(L"Tree"+to_wstring(i+1), ObjectLayer::InteractObject);
					mouse->SetHpMax(10);
					mouse->SetTileCountX(1);
					mouse->SetTileCountY(1);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
				});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
			}
		}
		else if (bookType == BookType::NoninterectObject)
		{
			//Ÿ��ư �ʱ�ȭ
			mTileButton->SetIsSelect(false);
			mHouseButton->SetIsSelect(false);
			mInterectObjectButton->SetIsSelect(false);
			//�ȷ�Ʈ �ʱ�ȭ
			mPallete.clear();
			//������Ʈ��ư �ʱ�ȭ
			vector<GameObject*> tempButton = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::ObjectButton);
			if (tempButton.size() != NULL)
			{
				for (int i = 0; i < tempButton.size(); ++i)
				{
					tempButton[i]->SetIsDestroy(true);
				}
			}
			//������ �ʱ�ȭ
			mPage = 1;
			//������Ʈ��ư ����
			for (int i = 0; i < 11; ++i)
			{
				ObjectButton* objectButton = new ObjectButton(L"Grass"+to_wstring(i+1), mX - 250 + 70*(i%4), mY - 150+90*(i/4), [i]() {
					Mouse* mouse = new Mouse(L"Grass" + to_wstring(i + 1), ObjectLayer::NoninteractObject);
					mouse->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Mouse, mouse);
				});
				objectButton->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::ObjectButton, objectButton);
			}
		}
		mIsTypeChange = false;
	}
}



