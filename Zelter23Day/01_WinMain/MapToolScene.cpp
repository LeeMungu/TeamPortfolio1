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
	mTileCountX = 25;
	mTileCountY = 25;
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

	mTileList.assign(mTileCountY, vector<Tile*>());
	for (int y = 0; y < mTileList.size(); ++y)
	{
		for (int x = 0; x < mTileCountX; ++x)
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
	
	mCurrentPallete = nullptr;
	mCurrentLayer = TileLayer::normal;
	//아직 선택하지 않음을 표시
	mPickStartIndexX = -1;
	mPickStartIndexY = -1;
	mIsExtendTile = false;
}

void MapToolScene::Release()
{
	ObjectManager::GetInstance()->Release();
	//알아서해

	for (int y = 0; y < mTileCountY; ++y)
	{
		for (int x = 0; x < mTileCountX; ++x)
		{
			SafeDelete(mTileList[y][x]);
		}
	}
	if (mSaveButton != nullptr)
	{
		SafeDelete(mSaveButton);
	}
	if (mLoadButton != nullptr)
	{
		SafeDelete(mLoadButton);
	}
}

void MapToolScene::Update()
{
	ObjectManager::GetInstance()->Update();

	//카메라 보정값
	float cameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	float cameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;
	RECT bookRect = mToolBook->GetRect();//툴북 제외용
	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
	{
		//타일 늘이기
		if (mCurrentPallete == nullptr && !PtInRect(&bookRect,_mousePosition))
		{
			int indexX = (_mousePosition.x + cameraX) / TileSize;
			int indexY = (_mousePosition.y + cameraY) / TileSize;
			if (indexX == mTileCountX - 1 || indexY == mTileCountY - 1)
			{
				mPickStartIndexX = indexX;
				mPickStartIndexY = indexY;
				mIsExtendTile = true;
			}
		}
		//{{ 팔레트 픽~
		vector<vector<Tile*>> palletList = mToolBook->GetPalleteList();
		for (int y = 0; y < mToolBook->GetNowTilecountY(); ++y)
		{
			for (int x = 0; x < mToolBook->GetNowTilecountX(); ++x)
			{
				RECT palletRect = palletList[y][x]->GetRect();
				if (PtInRect(&palletRect, _mousePosition))
				{
					mCurrentPallete = palletList[y][x];
					mToolBook->SetIsRoofOn(false);
				}
			}
		}
		// }}
	}

	if (Input::GetInstance()->GetKey(VK_LBUTTON))
	{
		int indexX = (_mousePosition.x + cameraX) / TileSize;
		int indexY = (_mousePosition.y + cameraY) / TileSize;
		//타일 늘이기
		if (mCurrentPallete == nullptr && mIsExtendTile ==true 
			&& (mPickStartIndexY != indexY||mPickStartIndexX != indexX))
		{
			indexX = (_mousePosition.x + cameraX) / TileSize;
			indexY = (_mousePosition.y + cameraY) / TileSize;
			//Y축 증
			if (mPickStartIndexY < indexY)
			{
				int plusIndex = indexY - mPickStartIndexY;
				for (int i = 0; i < plusIndex; i++)
				{
					mTileList.push_back(vector<Tile*>());
				}
				for (int y = mPickStartIndexY-1; y < mTileList.size(); ++y)
				{
					for (int x = 0; x < mTileCountX; ++x)
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
				mPickStartIndexY = indexY;
				mTileCountY = mPickStartIndexY + 1;
			}
			//Y축 감
			else if (mPickStartIndexY > indexY)
			{
				int minusIndex = mPickStartIndexY - indexY;
				for (int i = 0; i < minusIndex; i++)
				{
					mTileList.pop_back();
				}
				mPickStartIndexY = indexY;
				mTileCountY = mPickStartIndexY + 1;
			}

			//X축 증
			if (mPickStartIndexX < indexX)
			{
				int plusIndex = indexX - mPickStartIndexY;
				
				for (int y = 0; y < mTileList.size(); ++y)
				{
					for (int i = mTileCountX; i < indexX+1; i++)
					{
						mTileList[y].push_back(new Tile
						(
							nullptr,
							TileSize * i,
							TileSize * y,
							TileSize,
							TileSize,
							0,
							0
						));
						mTileList[y][i]->SetTileLayer(TileLayer::normal);
					}
				}
				mPickStartIndexX = indexX;
				mTileCountX = mPickStartIndexX + 1;
			}
			//x축 감
			else if (mPickStartIndexX > indexX)
			{
				int minusIndex = mPickStartIndexY - indexY;

				for (int y = 0; y < mTileList.size(); ++y)
				{
					for (int i = 0; i < minusIndex; i++)
					{
						mTileList[y].pop_back();
					}
				}
				mPickStartIndexX = indexX;
				mTileCountX = mPickStartIndexX + 1;
			}
		}
		// {{ 타일 그리기~
	
		else if (mCurrentPallete != nullptr && !PtInRect(&bookRect,_mousePosition))
		{
			indexX = (_mousePosition.x + cameraX) / TileSize;
			indexY = (_mousePosition.y + cameraY) / TileSize;
			if (indexX >= 0 && indexX < mTileCountX && indexY >= 0 && indexY < mTileCountY)
			{
				if (mTileList[indexY][indexX]->mImage != mCurrentPallete->mImage ||
					mTileList[indexY][indexX]->mFrameIndexX != mCurrentPallete->mFrameIndexX ||
					mTileList[indexY][indexX]->mFrameIndexY != mCurrentPallete->mFrameIndexY)
				{
					if (mToolBook->GetIsRoofOn() == true)
					{
						mToolBook->RoofOnMode(indexX, indexY);
						mToolBook->SetIsRoofOn(false);
					}
					IBrushTile* command = new IBrushTile(mTileList[indexY][indexX], mCurrentPallete);
					PushCommand(command);
					mToolBook->SetIsRoofOn(false);
					//cout << "OnPushCommand" << endl;
				}
				mTileList[indexY][indexX]->mTileLayer = mCurrentLayer;
			}
		}
	}
	// }}
	if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
	{
		//초기화
		if (mIsExtendTile == true)
		{
			mIsExtendTile = false;
		}
	}


	//버튼 생성
	if (mToolBook->GetIsOpenBook() && mSaveButton == nullptr && mLoadButton == nullptr)
	{
		mSaveButton = new Button(L"Save", mToolBook->GetX() + mToolBook->GetSizeX() / 5, mToolBook->GetY(), 200, 50,
			bind(&MapToolScene::Save, this));
		mLoadButton = new Button(L"Load", mToolBook->GetX() + mToolBook->GetSizeX() / 5, mToolBook->GetY() + 100, 200, 50,
			bind(&MapToolScene::Load, this));
	}
	//버튼 업데이트
	if (mSaveButton != nullptr)
	{
		mSaveButton->Move(mToolBook->GetX() + mToolBook->GetSizeX() / 5, mToolBook->GetY());
		mSaveButton->Update();
	}
	if (mLoadButton != nullptr)
	{
		mLoadButton->Move(mToolBook->GetX() + mToolBook->GetSizeX() / 5, mToolBook->GetY() + 100);
		mLoadButton->Update();
	}
	//되감기
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		if (Input::GetInstance()->GetKeyDown('Z'))
		{
			Undo();
		}
	}
	//팔레트 픽 지우기
	if (Input::GetInstance()->GetKeyDown(VK_BACK))
	{
		mCurrentPallete = nullptr;
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
		for (int x = 0; x < mTileCountX; ++x)
		{
			mTileList[y][x]->Render(hdc);
			if (CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mTileList[y][x]->GetRect()))
			{
				++renderCount;
			}
		}
	}

	D2DRenderer::GetInstance()
		->RenderText(10, 10, to_wstring(renderCount).c_str(), 12);
	D2DRenderer::GetInstance()
		->RenderText(10, 40, L"WASD : 카메라 이동", 12);
	D2DRenderer::GetInstance()
		->RenderText(10, 70, L"Shift + ←→↑↓ : 책 이동", 12);
	D2DRenderer::GetInstance()
		->RenderText(10, 100, L"Lctrl : 테두리", 12);
	D2DRenderer::GetInstance()
		->RenderText(10, 130, L"Lctrl + Z : 되감기", 12);


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
	if (mSaveButton != nullptr)
	{
		mSaveButton->Render(hdc);
	}
	if (mLoadButton != nullptr)
	{
		mLoadButton->Render(hdc);
	}
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

		saveStream << mTileCountX;
		saveStream << ',';
		saveStream << mTileCountY;
		saveStream << endl;
		for (int y = 0; y < mTileCountY; ++y)
		{
			for (int x = 0; x < mTileCountX; ++x)
			{
				string str;
				wstring keyName;
				if(mTileList[y][x]->mImage != nullptr)
					keyName = mTileList[y][x]->mImage->GetKey();
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

		string bufferCount;
		getline(loadStream, bufferCount, ',');
		mTileCountX = stoi(bufferCount);
		getline(loadStream, bufferCount);
		mTileCountY = stoi(bufferCount);
		//초기화 후 삽입
		mTileList.clear();
		mTileList.assign(mTileCountY, vector<Tile*>());
		for (int y = 0; y < mTileList.size(); ++y)
		{
			for (int x = 0; x < mTileCountX; ++x)
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
		for (int y = 0; y < mTileCountY; ++y)
		{
			for (int x = 0; x < mTileCountX; ++x)
			{
				string key;
				int frameX;
				int frameY;
				string buffer;
				int layer;

				//쉼표 앞에까지
				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameY = stoi(buffer);
				//줄의 마지막 값
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

