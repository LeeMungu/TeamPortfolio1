#include "pch.h"
#include "MapToolScene.h"

#include "Tile.h"
#include "Image.h"
#include "Button.h"
#include "Camera.h"
#include <fstream>
#include "GameObject.h"
#include "Player.h"

void MapToolScene::Init()
{
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile");
	Image* houseImage = ImageManager::GetInstance()->FindImage(L"House");

	Camera* camera = new Camera;
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::camera, camera);

	//player = new Player("Player",150 ,150);
	//ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player);
	mToolBook = new MapToolBook;
	ObjectManager::GetInstance()->AddObject(ObjectLayer::ToolBook, mToolBook);
	ObjectManager::GetInstance()->Init();

	mTileList.assign(TileCountY, vector<Tile*>());
	for (int y = 0; y < mTileList.size(); ++y)
	{
		for (int x = 0; x < TileCountX; ++x)
		{
			mTileList[y].push_back(new Tile
			(
				nullptr,
				TileSize * x,
				TileSize * y,
				TileSize,
				TileSize,
				0,
				0
			));
			mTileList[y][x]->SetTileLayer(TileLayer::normal);
		}
	}
	//버튼
	mSaveButton = new Button(L"Save", mToolBook->GetX()+mToolBook->GetSizeX()/5, mToolBook->GetY(), 200, 50,
		bind(&MapToolScene::Save, this));
	mLoadButton = new Button(L"Load", mToolBook->GetX() + mToolBook->GetSizeX() / 5, mToolBook->GetY() + 100, 200, 50,
		bind(&MapToolScene::Load, this));

	mCurrentPallete = nullptr;
	mCurrentLayer = TileLayer::normal;
}

void MapToolScene::Release()
{
	ObjectManager::GetInstance()->Release();
	//알아서해

	for (int y = 0; y < TileCountY; ++y)
	{
		for (int x = 0; x < TileCountX; ++x)
		{
			SafeDelete(mTileList[y][x]);
		}
	}
	SafeDelete(mSaveButton);
	SafeDelete(mLoadButton);
}

void MapToolScene::Update()
{
	ObjectManager::GetInstance()->Update();

	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		vector<vector<Tile*>> palletList = mToolBook->GetPalleteList();
		//{{ 팔레트 픽~
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 8; ++x)
			{
				RECT palletRect = palletList[y][x]->GetRect();
				if (PtInRect(&palletRect, _mousePosition))
				{
					mCurrentPallete = palletList[y][x];
				}
			}
		}
		// }}
	}

	float cameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	float cameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;

	// {{ 타일 그리기~
	if (Input::GetInstance()->GetKey(VK_LBUTTON))
	{
		if (mCurrentPallete != nullptr)
		{
			int indexX = (_mousePosition.x + cameraX) / TileSize;
			int indexY = (_mousePosition.y + cameraY) / TileSize;
			if (indexX >= 0 && indexX < TileCountX && indexY >= 0 && indexY < TileCountY)
			{
				if (mTileList[indexY][indexX]->mImage != mCurrentPallete->mImage ||
					mTileList[indexY][indexX]->mFrameIndexX != mCurrentPallete->mFrameIndexX ||
					mTileList[indexY][indexX]->mFrameIndexY != mCurrentPallete->mFrameIndexY)
				{
					IBrushTile* command = new IBrushTile(mTileList[indexY][indexX], mCurrentPallete);
					PushCommand(command);
					//cout << "OnPushCommand" << endl;
				}
				mTileList[indexY][indexX]->mTileLayer = mCurrentLayer;
			}
		}
	}
	// }}

	mSaveButton->Move(mToolBook->GetX() + mToolBook->GetSizeX() / 5, mToolBook->GetY());
	mLoadButton->Move(mToolBook->GetX() + mToolBook->GetSizeX() / 5, mToolBook->GetY() + 100);
	//버튼 업데이트
	mSaveButton->Update();
	mLoadButton->Update();
	//되감기
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			Undo();
		}
	}
}

void MapToolScene::Render(HDC hdc)
{
	Camera* mainCamera = CameraManager::GetInstance()->GetMainCamera();

	////카메라에 맞춰서 타일을 그려줌
	//int leftIndex = Math::Clamp(mainCamera->GetRect().left / TileSize, 0, TileCountX - 1);
	//int rightIndex = Math::Clamp(mainCamera->GetRect().right / TileSize, 0, TileCountX - 1);	
	//int topIndex = Math::Clamp(mainCamera->GetRect().top / TileSize, 0, TileCountY - 1);
	//int bottomIndex = Math::Clamp(mainCamera->GetRect().bottom / TileSize,0,TileCountY - 1);
	//
	//int renderCount = 0;
	//for (int y = topIndex; y <= bottomIndex; ++y)
	//{
	//	for (int x = leftIndex; x <= rightIndex; ++x)
	//	{
	//		mTileList[y][x]->Render(hdc);
	//		++renderCount;
	//	}
	//}

	//카메라의 스케일프레임렌더만 내부에서 클렘핑 판정해줌 봐서 기타 오브젝트도 고쳐볼것
	int renderCount = 0;
	for (int y = 0; y < mTileList.size(); ++y)
	{
		for (int x = 0; x < TileCountX; ++x)
		{
			mTileList[y][x]->Render(hdc);
			if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mTileList[y][x]->GetRect()))
			{
				++renderCount;
			}
		}
	}

	TextOut(hdc, 10, 10, to_wstring(renderCount).c_str(), to_wstring(renderCount).length());
	TextOut(hdc, 10, 40, L"WASD : 카메라 이동", 12);
	TextOut(hdc, 10, 70, L"Shift + ←→↑↓ : 책 이동", 12);
	TextOut(hdc, 10, 100, L"Lctrl : 테두리", 12);
	TextOut(hdc, 10, 130, L"Lctrl + Z : 되감기", 12);


	if (mCurrentPallete != nullptr)
	{
		RECT miniRc = RectMake(_mousePosition.x - mCurrentPallete->GetSizeX() / 4, _mousePosition.y - mCurrentPallete->GetSizeY() / 4, mCurrentPallete->GetSizeX(), mCurrentPallete->GetSizeY());
		mCurrentPallete->mImage->ScaleFrameRender(hdc, _mousePosition.x - mCurrentPallete->GetSizeX() / 4, _mousePosition.y - mCurrentPallete->GetSizeY() / 4,
			mCurrentPallete->mFrameIndexX, mCurrentPallete->mFrameIndexY, mCurrentPallete->GetSizeX(), mCurrentPallete->GetSizeY());
		if (mCurrentLayer == TileLayer::wall)
			Gizmo::GetInstance()->DrawRect(hdc, miniRc, Gizmo::Color::Red);
		else if (mCurrentLayer == TileLayer::slow)
			Gizmo::GetInstance()->DrawRect(hdc, miniRc, Gizmo::Color::Blue);
		else
			Gizmo::GetInstance()->DrawRect(hdc, miniRc, Gizmo::Color::Green);
	}
	ObjectManager::GetInstance()->Render(hdc);

	//버튼 그려주기
	mSaveButton->Render(hdc);
	mLoadButton->Render(hdc);

	//카메라렉트 테스트용
	//RenderRect(hdc,CameraManager::GetInstance()->GetMainCamera()->GetRect());
}

void MapToolScene::Save()
{
	ofstream saveStream(L"../04_Data/Test.txt");
	if (saveStream.is_open())
	{
		string tempImageKey;
		int frameX;
		int frameY;

		for (int y = 0; y < TileCountY; ++y)
		{
			for (int x = 0; x < TileCountX; ++x)
			{
				string str;
				wstring keyName;
				if(mTileList[y][x]->mImage != nullptr)
					keyName = mTileList[y][x]->mImage->GetKeyName();
				str.assign(keyName.begin(), keyName.end());

				saveStream << str.c_str();
				saveStream << ',';
				saveStream << mTileList[y][x]->mFrameIndexX;
				saveStream << ',';
				saveStream << mTileList[y][x]->mFrameIndexY;
				saveStream << ',';
				saveStream << (int)mTileList[y][x]->mTileLayer;
				saveStream << endl;
			}
		}
	}
}

void MapToolScene::Load()
{
	ifstream loadStream(L"../04_Data/Test.txt");
	if (loadStream.is_open())
	{
		for (int y = 0; y < TileCountY; ++y)
		{
			for (int x = 0; x < TileCountX; ++x)
			{
				string key;
				int frameX;
				int frameY;
				string buffer;
				int layer;

				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameY = stoi(buffer);
				getline(loadStream, buffer);
				layer = stoi(buffer);

				wstring wstr;
				wstr.assign(key.begin(), key.end());
				mTileList[y][x]->mImage = ImageManager::GetInstance()->FindImage(wstr);
				mTileList[y][x]->mFrameIndexX = frameX;
				mTileList[y][x]->mFrameIndexY = frameY;
				mTileList[y][x]->mTileLayer = (TileLayer)layer;
			}
		}
	}
}

void MapToolScene::MakeNormal()
{
}

void MapToolScene::MakeSlow()
{
}

void MapToolScene::MakeWall()
{
}



void MapToolScene::PushCommand(ICommand * command)
{
	command->Execute();
	mCommandList.emplace(command);
}

void MapToolScene::Undo()
{
	if (mCommandList.size() == 0)
		return;

	mCommandList.top()->Undo();
	mRedoList.emplace();
	mCommandList.pop();
}

