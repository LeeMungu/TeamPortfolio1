#include "pch.h"
#include "scene1.h"

#include "Tile.h"
#include "Image.h"
#include "Button.h"
#include "Camera.h"
#include <fstream>
#include "GameObject.h"
#include "Player.h"
#include "SmartWatch.h"
void scene1::Init()
{
	mSmartWatch = new SmartWatch("SmartWatch");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mSmartWatch);


	Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile");

	player = new Player("Player", 150, 150);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, player);
	ObjectManager::GetInstance()->Init();

	

	Camera* camera = new Camera;
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::camera, camera);

	for (int y = 0; y < TileCountY; ++y)
	{
		for (int x = 0; x < TileCountX; ++x)
		{
			mTileList[y][x] = new Tile
			(
				tileImage,
				TileSize * x,
				TileSize * y,
				TileSize,
				TileSize,
				//Random::GetInstance()->RandomInt(3),
				4,
				0
			);
			mTileList[y][x]->SetTileLayer(TileLayer::normal);
		}
	}

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

void scene1::Release()
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
}


void scene1::Update()
{
	ObjectManager::GetInstance()->Update();



	Player* tempPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	int playerIndexX = tempPlayer->GetX() / TileSize;
	int playerIndexY = tempPlayer->GetY() / TileSize;


	for (int y = playerIndexY - 1; y <= playerIndexY + 1; ++y)
	{
		if (y < 0)continue;
		for (int x = playerIndexX - 1; x <= playerIndexX + 1; ++x)
		{
			if (x < 0)continue;

			RECT temp;
			RECT playerRect = tempPlayer->GetRect();
			RECT tileRect = mTileList[y][x]->GetRect();
			if (IntersectRect(&temp, &tileRect, &playerRect))
			{
				if (mTileList[y][x]->GetTileLayer() == TileLayer::slow)
				{
					tempPlayer->SetSpeed(1.f);
				}
				else if (mTileList[y][x]->GetTileLayer() == TileLayer::normal)
				{
					tempPlayer->SetSpeed(3.f);
				}
				else if (mTileList[y][x]->GetTileLayer() == TileLayer::wall)
				{
					float tempW = temp.right - temp.left;
					float tempH = temp.bottom - temp.top;
					float tempX = temp.left + tempW / 2;
					float tempY = temp.top + tempW / 2;

					float tileRectX = tileRect.left + (tileRect.right - tileRect.left) / 2;
					float tileRectY = tileRect.top + (tileRect.bottom - tileRect.top) / 2;

					if (tempW < tempH && tempX > tileRectX && playerRect.left < tileRect.right)
					{
						tempPlayer->SetX(tileRect.right + tempPlayer->GetSizeX() / 2);
					}

					if (tempW < tempH && tempX < tileRectX && playerRect.right > tileRect.left)
					{
						tempPlayer->SetX(tileRect.left - tempPlayer->GetSizeX() / 2);
					}

					if (tempW > tempH && tempY > tileRectY && playerRect.top < tileRect.bottom)
					{
						tempPlayer->SetY(tileRect.bottom + tempPlayer->GetSizeY() / 2);
					}

					if (tempW > tempH && tempY < tileRectY && playerRect.bottom > tileRect.top)
					{
						tempPlayer->SetY(tileRect.top - tempPlayer->GetSizeY() / 2);
					}
				}
			}
		}
	}
	float cameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	float cameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;


}

void scene1::Render(HDC hdc)
{

	Camera* mainCamera = CameraManager::GetInstance()->GetMainCamera();


	//카메라에 맞춰서 타일을 그려줌
	int leftIndex = Math::Clamp(mainCamera->GetRect().left / TileSize, 0, TileCountX - 1);
	int rightIndex = Math::Clamp(mainCamera->GetRect().right / TileSize, 0, TileCountX - 1);
	int topIndex = Math::Clamp(mainCamera->GetRect().top / TileSize, 0, TileCountY - 1);
	int bottomIndex = Math::Clamp(mainCamera->GetRect().bottom / TileSize, 0, TileCountY - 1);

	int renderCount = 0;

	for (int y = 0; y < TileCountY; ++y)
	{
		for (int x = 0; x < TileCountX; ++x)
		{
			mTileList[y][x]->Render(hdc);
			++renderCount;
		}
	}

	TextOut(hdc, 10, 10, to_wstring(renderCount).c_str(), to_wstring(renderCount).length());

	ObjectManager::GetInstance()->Render(hdc);
}
