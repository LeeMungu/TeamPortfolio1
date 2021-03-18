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
#include "Zombie01.h"
#include "Zombie02.h"
#include "InteractObject.h"
#include "NonInteractObject.h"
#include "CollisionManager.h"
#include "KeyIcon.h"
#include "QuickSlot.h"
void scene1::Init()
{
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile");

	mPlayer = new Player("Player", 150, 150);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);
 


	
	mSmartWatch = new SmartWatch("SmartWatch", 5, 5);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mSmartWatch);
	mSmartWatch->SetPlayer(mPlayer);

	Camera* camera = new Camera;
	camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::camera, camera);
	

	KeyIcon* keyIcon = new KeyIcon("KeyIcon");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, keyIcon);

	QuickSlot* quickSlot = new QuickSlot("QuickSlot");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, quickSlot);

	Load();
	Zombie01* mZombie01 = new Zombie01();
	mZombie01->SetTileList(mTileList);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mZombie01);
	Zombie02* mZombie02 = new Zombie02();
	mZombie02->SetTileList(mTileList);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, mZombie02);


	ObjectManager::GetInstance()->Init();
	CollisionManager::GetInstance()->Init();
	camera->ChangeMode(Camera::Mode::Follow);

	//true �����ϸ� �� �ð� �帧
	Time::GetInstance()->SetIsSceneStart(true);
}

void scene1::Release()
{
	ObjectManager::GetInstance()->Release();
	//�˾Ƽ���
	for (int y = 0; y < mTileList.size(); ++y)
	{
		for (int x = 0; x < mTileCountX; ++x)
		{
			SafeDelete(mTileList[y][x]);
		}
	}
}


void scene1::Update()
{
	ObjectManager::GetInstance()->Update();
	CollisionManager::GetInstance()->Update();


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

				}
			}
		}
	}
	//float cameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	//float cameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;

}

void scene1::Render(HDC hdc)
{

	Camera* mainCamera = CameraManager::GetInstance()->GetMainCamera();


	//ī�޶� ���缭 Ÿ���� �׷���
	int leftIndex = Math::Clamp(mainCamera->GetRect().left / TileSize, 0, mTileCountX - 1);
	int rightIndex = Math::Clamp(mainCamera->GetRect().right / TileSize, 0, mTileCountX - 1);
	int topIndex = Math::Clamp(mainCamera->GetRect().top / TileSize, 0, mTileCountY - 1);
	int bottomIndex = Math::Clamp(mainCamera->GetRect().bottom / TileSize, 0, mTileCountY - 1);

	int renderCount = 0;

	for (int y = 0; y < mTileList.size(); ++y)
	{
		for (int x = 0; x < mTileCountX; ++x)
		{
			if(CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mTileList[y][x]->GetRect()))
				mTileList[y][x]->Render(hdc);
			++renderCount;
		}
	}

	//TextOut(hdc, 10, 10, to_wstring(renderCount).c_str(), to_wstring(renderCount).length());

	ObjectManager::GetInstance()->Render(hdc);

	//�� �ð� ����
	float worldTime = Time::GetInstance()->GetWorldTime();
	float sceneTime = Time::GetInstance()->GetSceneTime();
	wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	wstring strSceneTime = L"ScneTime : " + to_wstring(sceneTime);
	D2DRenderer::GetInstance()
		->RenderText(10, 200, strWorldTime.c_str(), strWorldTime.length());
	D2DRenderer::GetInstance()
		->RenderText(10, 280, strSceneTime.c_str(), strSceneTime.length());
}

void scene1::Load()
{

	ifstream loadStream(L"../04_Data/Test.txt");
	if (loadStream.is_open())
	{

		string bufferCount;
		getline(loadStream, bufferCount, ',');
		mTileCountX = stoi(bufferCount);
		getline(loadStream, bufferCount);
		mTileCountY = stoi(bufferCount);
		//�ʱ�ȭ �� ����
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
					x,
					y,
					x,
					y
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

				//��ǥ �տ�����
				getline(loadStream, buffer, ',');
				key = buffer;
				getline(loadStream, buffer, ',');
				frameX = stoi(buffer);
				getline(loadStream, buffer, ',');
				frameY = stoi(buffer);
				//���� ������ ��
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
		//������Ʈ�� ����
		vector<GameObject*> tempObject = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::HousingObject);
		if (tempObject.size() != NULL)
		{
			for (int i = 0; i < tempObject.size(); ++i)
			{
				tempObject[i]->SetIsDestroy(true);
			}
		}
		vector<GameObject*> tempObject1 = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);
		if (tempObject1.size() != NULL)
		{
			for (int i = 0; i < tempObject1.size(); ++i)
			{
				tempObject1[i]->SetIsDestroy(true);
			}
		}
		vector<GameObject*> tempObject2 = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::NoninteractObject);
		if (tempObject2.size() != NULL)
		{
			for (int i = 0; i < tempObject2.size(); ++i)
			{
				tempObject2[i]->SetIsDestroy(true);
			}
		}

		//������Ʈ �о����
		string bufferObjectLayer;//���̾�
		//�� �о����
		getline(loadStream, bufferObjectLayer, ',');
		string buffer;
		ObjectLayer objectLayer = (ObjectLayer)stoi(bufferObjectLayer);
		getline(loadStream, buffer);
		int objectSize = stoi(buffer);
		//���̾�, ����
		if (objectSize != NULL)
		{
			for (int i = 0; i < objectSize; ++i)
			{
				wstring imageKey;
				int x, y;
				getline(loadStream, buffer, ',');
				imageKey.assign(buffer.begin(), buffer.end());
				getline(loadStream, buffer, ',');
				x = stoi(buffer);
				getline(loadStream, buffer);
				y = stoi(buffer);
				//�Ͽ�¡ ���� <-���Ŀ� �ؿ� ������ �������ٿ���
				// ������ �Ű������� �� �ø� ����?
				//HousingObject* temp = new HousingObject(imageKey, x, y);
				//temp->Init();
				//ObjectManager::GetInstance()->AddObject(objectLayer, temp);
			}
		}
		//���ͷ�Ʈ �о����
		getline(loadStream, bufferObjectLayer, ',');
		objectLayer = (ObjectLayer)stoi(bufferObjectLayer);
		getline(loadStream, buffer);
		objectSize = stoi(buffer);
		//���̾�, ����
		if (objectSize != NULL)
		{
			for (int i = 0; i < objectSize; ++i)
			{
				wstring imageKey;
				int x, y;
				int hp, tileCountX, tileCountY;
				getline(loadStream, buffer, ',');
				imageKey.assign(buffer.begin(), buffer.end());
				getline(loadStream, buffer, ',');
				x = stoi(buffer);
				getline(loadStream, buffer, ',');
				y = stoi(buffer);
				getline(loadStream, buffer, ',');
				hp = stoi(buffer);
				getline(loadStream, buffer, ',');
				tileCountX = stoi(buffer);
				getline(loadStream, buffer);
				tileCountY = stoi(buffer);
				//������ ���ͷ�Ʈ�ΰ��� Ȯ�������Ƿ� ���Ƿ� �ִ´�
				//����
				InteractObject* temp = new InteractObject(imageKey, x, y, hp, tileCountX, tileCountY);
				temp->Init();
				ObjectManager::GetInstance()->AddObject(objectLayer, temp);
			}
		}
		//�����ͷ�Ʈ �о����
		getline(loadStream, bufferObjectLayer, ',');
		//������-�Ͽ콺, ���ͷ�Ʈ, �����ͷ�Ʈ	
		objectLayer = (ObjectLayer)stoi(bufferObjectLayer);
		getline(loadStream, buffer);
		objectSize = stoi(buffer);
		//���̾�, ����
		if (objectSize != NULL)
		{
			for (int i = 0; i < objectSize; ++i)
			{
				wstring imageKey;
				int x, y;
				getline(loadStream, buffer, ',');
				imageKey.assign(buffer.begin(), buffer.end());
				getline(loadStream, buffer, ',');
				x = stoi(buffer);
				getline(loadStream, buffer);
				y = stoi(buffer);
				//������ �����ͷ�Ʈ�ΰ��� Ȯ�������Ƿ� ���Ƿ� �ִ´�
				//����
				NonInteractObject* temp = new NonInteractObject(imageKey, x, y);
				temp->Init();
				ObjectManager::GetInstance()->AddObject(objectLayer, temp);
			}
		}
		//Ÿ�ϼӼ� �ٲ��ֱ����� �ʱ�ȭ���ֱ�
		for (int y = 0; y < mTileCountY; ++y)
		{
			for (int x = 0; x < mTileCountX; ++x)
			{
				mTileList[y][x]->SetTileLayer(TileLayer::normal);
			}
		}
		//���ͷ�Ʈ ������Ʈ�� ���� Ÿ�� �Ӽ� �ٲٱ�(wall�� �ٲ��ֱ�)
		//�ε� �Ҷ��� ����� �ҵ��ϴ� -> �׻� ����Ǿ���Ѵ� -> ������Ʈ�Ŵ������� ���ְ� ������ Ÿ���� ������Ʈ�Ŵ����� ����.
		//->Ÿ���� ������Ʈ�Ŵ����� �ֱ�� �޸�Ʈ�� �ʹ� ����(������Ʈ�� ��Ÿ�κ��� �ǹ̰� ���� Ÿ���� Ÿ�Ϸ� ���ܵδ°� �浹�� ���� 
		//Ÿ���� ���� ����
		vector<GameObject*> tempInteractList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);
		if (tempInteractList.size() != NULL)
		{
			for (int i = 0; i < tempInteractList.size(); ++i)
			{
				if (tempInteractList[i]->GetIsDestroy() != true)
				{
					InteractObject* tempInteract = (InteractObject*)tempInteractList[i];
					int y = 0;
					int countx = tempInteract->GetTileCountX() * InteractObjectSize;
					int county = tempInteract->GetTileCountY() * InteractObjectSize;
					for (int x = 0; x < countx * county; ++x)
					{
						if (mTileList[(int)(tempInteract->GetTileIndexY()) - (x / countx)][(int)(tempInteract->GetTileIndexX()) + (x % countx)]->GetTileLayer() != TileLayer::wall)
							mTileList[(int)(tempInteract->GetTileIndexY()) - (x / countx)][(int)(tempInteract->GetTileIndexX()) + (x % countx)]->SetTileLayer(TileLayer::wall);
					}
				}
			}
		}
	}
}
