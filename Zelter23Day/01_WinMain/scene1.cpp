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
#include "Inventory.h"
#include "HousingObject.h"
#include "Tablet.h"
#include "WorkTable.h"
#include "ItemManager.h"

//��
#include "Evening.h"
//�̺�Ʈ
#include "GameEvent.h"
#include "Weapon.h"
#include "Bomb.h"
void scene1::Init()
{
	Image* tileImage = ImageManager::GetInstance()->FindImage(L"Tile");

	mPlayer = new Player("Player", 1300, 1400);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Player, mPlayer);

	
	mSmartWatch = new SmartWatch("SmartWatch", 5, 5);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, mSmartWatch);

	Camera* camera = new Camera;
	camera->SetTarget(mPlayer);
	CameraManager::GetInstance()->SetMainCamera(camera);
	ObjectManager::GetInstance()->AddObject(ObjectLayer::camera, camera);
	

	KeyIcon* keyIcon = new KeyIcon("KeyIcon");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, keyIcon);

	Inventory* inventory = new Inventory("Inventory");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, inventory);

	QuickSlot* quickSlot = new QuickSlot("QuickSlot");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, quickSlot);


	Tablet* tablet = new Tablet("Tablet");
	ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, tablet);

	//��
	Evening* evening = new Evening();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Weater, evening);

	Load();

	ItemManager::GetInstance()->Init();
	ObjectManager::GetInstance()->Init();
	CollisionManager::GetInstance()->Init();
	camera->ChangeMode(Camera::Mode::Follow);

	//true �����ϸ� �� �ð� �帧
	Time::GetInstance()->SetIsSceneStart(true);
	mZombieCount = 100;
	mZombieCoolTime = 1; // ���� ��Ÿ��
	mZombieCoolTimer = 0;//��ŸŸ�� ������ Ÿ�̸�

	SoundPlayer::GetInstance()->Play(L"BGM", 0.5f * SoundPlayer::GetInstance()->GetBgmVolume());
	SoundPlayer::GetInstance()->Play(L"ForestSound", 0.2f * SoundPlayer::GetInstance()->GetBgmVolume());
	SoundPlayer::GetInstance()->Stop(L"Siren1");

	//�̺�Ʈ �ʱ�ȭ 
	GameEventManager::GetInstance()->RemoveAllEvent();
	//�н����δ����� ���� �Ŀ� ��������
	//for (int i = 0; i < 1; ++i)
	//{
	//	GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(1000, 1600, mTileList));
	//}
	//ù ���� �� �ؽ�Ʈ â ���
	GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(0.5f));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"�����ÿ� ���ε���\n���� �ִٰ�����.\n���� ���� ���������� ������."));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(4.f, L"�ٵ� ��������� �����ٵ�.\n������� ���� ��������\n�������� ����̾�."));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(4.f, L"Ȥ�� ���� �濡 �ִ� ����������\n������ �ֿ� �� ������ ����."));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(4.f, L"�켱 ������ �ִ� ������\n�༮���� �������."));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"���� ���� �� FŰ�� ������\n���� ������ �� �ֽ��ϴ�."));
	GameEventManager::GetInstance()->PushEvent(new IAllUnitActive());

	//Ư�� ��� ���� �� ������� �� ���� �ؽ�Ʈâ ���
	GameEventManager::GetInstance()->PushEvent(new ITileEvent(ITileEvent::Mode::DownRight,TileSize*84,TileSize*125));
	GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"�� ���� ���󰡸� �����̾�."));
	GameEventManager::GetInstance()->PushEvent(new IAllUnitActive());

	//Ż�� �� ��ź ���� �̺�Ʈ �ȳ� �ؽ�Ʈâ ���
	GameEventManager::GetInstance()->
		PushEvent(new IObjectCrushEvent(
			ObjectManager::GetInstance()->FindObject(ObjectLayer::InteractObject, "Barricade2"),
			ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")));
	
		GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"�������� ������ ��������\n�����ϴµ� ���� �����ִ�..."));
		GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f));
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"�Ƹ� ������ź����\n���� ���� �� �����ž�."));
		GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f));
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"�ֺ��� ���ƴٴϸ鼭\n��Ḧ ��ƺ���."));
		GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f));
		GameEventManager::GetInstance()->PushEvent(new IAllUnitActive());
	
		//���� ���� �̺�Ʈ
		
		GameEventManager::GetInstance()->PushEvent(new ITileEvent(ITileEvent::Mode::UpRight, TileSize * 232, TileSize * 68));
		GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"ǥ���ǿ� �������� ���ϰ�\n�ְ��� �� �޸� ���δ�."));
		GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f));
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"���Ϳ� �ܿ� �������\n���Ƴ־����� �༮����\n�����ϴ� �ൿ�� ������ ��\n���å�Ӿ���."));
		GameEventManager::GetInstance()->PushEvent(new IAllUnitActive());
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 219, TileSize * 39, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 225, TileSize * 44, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 235, TileSize * 41, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 245, TileSize * 48, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 236, TileSize * 53, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 224, TileSize * 53, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 222, TileSize * 57, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 226, TileSize * 63, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 217, TileSize * 53, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 218, TileSize * 46, mTileList));
		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(TileSize * 243, TileSize * 43, mTileList));


		//���� �� ����
		GameEventManager::GetInstance()->PushEvent(new ITileEvent(ITileEvent::Mode::UpRight, TileSize * 267, TileSize * 114));
		GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"���� ���� ������."));
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"�ٵ� ��������."));
		//GameEventManager::GetInstance()->PushEvent(new IGameEnding(true));


		//for (int i = 0; i < 1; ++i)
		//	{
		//		GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(1000, 1600, mTileList));
		//	}

	//WeatherManager::GetInstance()->Init();
	//WeatherManager::GetInstance()->SetWeather(WeatherMode::Rain);

	ItemManager::GetInstance()->DropItems(L"Pistol", 6000, 3450, 1);

}

void scene1::Release()
{
	GameEventManager::GetInstance()->RemoveAllEvent();
	ObjectManager::GetInstance()->Release();
	//WeatherManager::GetInstance()->Release();
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
	//Weather
	//WeatherManager::GetInstance()->Update();
	
	//�̺�Ʈ
	GameEventManager::GetInstance()->Update();

	ObjectManager::GetInstance()->Update();
	CollisionManager::GetInstance()->Update();

	ItemManager::GetInstance()->Update();


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


	//Ÿ�ϼӼ� �ٲ��ֱ����� �ʱ�ȭ���ֱ�
	//ī�޶� ���缭 Ÿ���� �׷���
	Camera* mainCamera = CameraManager::GetInstance()->GetMainCamera();
	int leftIndex = Math::Clamp(mainCamera->GetRect().left / TileSize, 0, mTileCountX - 1);
	int rightIndex = Math::Clamp(mainCamera->GetRect().right / TileSize, 0, mTileCountX - 1);
	int topIndex = Math::Clamp(mainCamera->GetRect().top / TileSize, 0, mTileCountY - 1);
	int bottomIndex = Math::Clamp(mainCamera->GetRect().bottom / TileSize, 0, mTileCountY - 1);

	for (int y = topIndex; y < bottomIndex; ++y)
	{
		for (int x = leftIndex; x < rightIndex; ++x)
		{
			mTileList[y][x]->SetTileLayer(TileLayer::normal);
		}
	}
	//���ͷ�Ʈ ������Ʈ�� ���� Ÿ�� �Ӽ� �ٲٱ�(wall�� �ٲ��ֱ�)
	//�ε� �Ҷ��� ����� �ҵ��ϴ� -> �׻� ����Ǿ���Ѵ� -> ������Ʈ�Ŵ������� ���ְ� ������ Ÿ���� ������Ʈ�Ŵ����� ����.
	//->Ÿ���� ������Ʈ�Ŵ����� �ֱ�� �޸�Ʈ�� �ʹ� ����(������Ʈ�� ��Ÿ�κ��� �ǹ̰� ���� Ÿ���� Ÿ�Ϸ� ���ܵδ°� �浹�� ���� 
	//Ÿ���� ���� ����
	vector<GameObject*> tempInteractList = ObjectManager::GetInstance()->GetClipingInteraceList();
	if (tempInteractList.size() != NULL)
	{
		for (int i = 0; i < tempInteractList.size(); ++i)
		{
			if (tempInteractList[i]->GetIsDestroy() != true)
			{
				InteractObject* tempInteract = (InteractObject*)tempInteractList[i];
				wstring tempKey = tempInteract->GetImageKey().substr(0, 4);
				if (tempKey == L"Door")
				{
					continue;
				}
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
	//���� Ÿ�� ó��
	vector<RECT> tempHousingWallList = ObjectManager::GetInstance()->GetClipingHousingWall();
	if (tempHousingWallList.size() != NULL)
	{
		for (int i = 0; i < tempHousingWallList.size(); ++i)
		{
			int startWallTileX = (int)(tempHousingWallList[i].left / TileSize);
			int startWallTileY = (int)(tempHousingWallList[i].top / TileSize);
			int endWallTileX = (int)(tempHousingWallList[i].right / TileSize);
			int endWallTileY = (int)(tempHousingWallList[i].bottom / TileSize);
			int wallTileCountX = endWallTileX - startWallTileX + 1;
			int wallTileCountY = endWallTileY - startWallTileY + 1;
			for (int j = 0; j < wallTileCountX * wallTileCountY; ++j)
			{
				if (mTileList[startWallTileY + j / wallTileCountX][startWallTileX + j % wallTileCountX]->GetTileLayer() != TileLayer::wall)
				{
					mTileList[startWallTileY + j / wallTileCountX][startWallTileX + j % wallTileCountX]->SetTileLayer(TileLayer::wall);
				}
			}
		}
	}

	
	float randomX = Random::GetInstance()->RandomInt(TileSize+1, TileSize * (mTileCountX-1));
	float randomY = Random::GetInstance()->RandomInt(TileSize+1, TileSize * (mTileCountY-1));
	
	//if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy).size() < mZombieCount)
	//{
	//	mZombieCoolTimer += Time::GetInstance()->DeltaTime();
	//	if (mZombieCoolTimer > mZombieCoolTime)
	//	{
	//		EnemyRespown(randomX, randomY);
	//		mZombieCoolTimer = 0;
	//	}
	//	
	//}

	if (Input::GetInstance()->GetKeyDown('C'))
	{
		if (mIsWorkTable == false)
		{
			WorkTable* workTable = new WorkTable("WorkTable");
			workTable->Init();
			workTable->SetTableOpen(true);
			ObjectManager::GetInstance()->AddObject(ObjectLayer::UI, workTable);
			mIsWorkTable = true;
			//mPlayer->WeaponUse(false);
		}
		else
		{
			WorkTable* tempTable = (WorkTable*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "WorkTable");
			tempTable->SetTableOpen(false);
			tempTable->DeleteItem();
			tempTable->SetIsDestroy(true);
			mIsWorkTable = false;
			//mPlayer->WeaponUse(true);
		}
	}
	
	if (GameEventManager::GetInstance()->GetEventCount() == 0)
	{
		SceneManager::GetInstance()->LoadScene(L"EndingScene");
		SoundPlayer::GetInstance()->Stop(L"BGM");
	}
}

void scene1::Render(HDC hdc)
{

	//ī�޶� ���缭 Ÿ���� �׷���
	Camera* mainCamera = CameraManager::GetInstance()->GetMainCamera();
	int leftIndex = Math::Clamp(mainCamera->GetRect().left / TileSize, 0, mTileCountX - 1);
	int rightIndex = Math::Clamp(mainCamera->GetRect().right / TileSize, 0, mTileCountX - 1);
	int topIndex = Math::Clamp(mainCamera->GetRect().top / TileSize, 0, mTileCountY - 1);
	int bottomIndex = Math::Clamp(mainCamera->GetRect().bottom / TileSize, 0, mTileCountY - 1);

	int renderCount = 0;

	for (int y = topIndex; y < bottomIndex+1; ++y)
	{
		for (int x = leftIndex; x < rightIndex+1; ++x)
		{
			if(CameraManager::GetInstance()->GetMainCamera()->IsInCameraArea(mTileList[y][x]->GetRect()))
				mTileList[y][x]->Render(hdc);
			++renderCount;
			//�̺�Ʈ �׽��ÿ� ������ ����!
			//CameraManager::GetInstance()->GetMainCamera()->RenderText(
			//	mTileList[y][x]->GetX(), mTileList[y][x]->GetY(),
			//	to_wstring(x)+L","+ to_wstring(y),
			//	10);
		}
	}

	//TextOut(hdc, 10, 10, to_wstring(renderCount).c_str(), to_wstring(renderCount).length());

	ObjectManager::GetInstance()->Render(hdc);
	//�� �ð� ����
	//float worldTime = Time::GetInstance()->GetWorldTime();
	//float sceneTime = Time::GetInstance()->GetSceneTime();
	//wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	//wstring strSceneTime = L"ScneTime : " + to_wstring(sceneTime);
	//D2DRenderer::GetInstance()
	//	->RenderText(10, 200, strWorldTime.c_str(), strWorldTime.length());
	//D2DRenderer::GetInstance()
	//	->RenderText(10, 280, strSceneTime.c_str(), strSceneTime.length());
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
				int tileCountX, tileCountY;
				getline(loadStream, buffer, ',');
				imageKey.assign(buffer.begin(), buffer.end());
				getline(loadStream, buffer, ',');
				x = stoi(buffer);
				getline(loadStream, buffer, ',');
				y = stoi(buffer);
				getline(loadStream, buffer, ',');
				tileCountX = stoi(buffer);
				getline(loadStream, buffer);
				tileCountY = stoi(buffer);
				//�Ͽ�¡ ���� <-���Ŀ� �ؿ� ������ �������ٿ���
				// ������ �Ű������� �� �ø� ����?
				HousingObject* temp = new HousingObject(imageKey, x, y, tileCountX, tileCountY);
				temp->Init();
				ObjectManager::GetInstance()->AddObject(objectLayer, temp);
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
		//ī�޶� ���缭 Ÿ���� �׷���
		Camera* mainCamera = CameraManager::GetInstance()->GetMainCamera();
		int leftIndex = Math::Clamp(mainCamera->GetRect().left / TileSize, 0, mTileCountX - 1);
		int rightIndex = Math::Clamp(mainCamera->GetRect().right / TileSize, 0, mTileCountX - 1);
		int topIndex = Math::Clamp(mainCamera->GetRect().top / TileSize, 0, mTileCountY - 1);
		int bottomIndex = Math::Clamp(mainCamera->GetRect().bottom / TileSize, 0, mTileCountY - 1);

		for (int y = topIndex; y < bottomIndex; ++y)
		{
			for (int x = leftIndex; x < rightIndex; ++x)
			{
				mTileList[y][x]->SetTileLayer(TileLayer::normal);
			}
		}
		//���ͷ�Ʈ ������Ʈ�� ���� Ÿ�� �Ӽ� �ٲٱ�(wall�� �ٲ��ֱ�)
		//�ε� �Ҷ��� ����� �ҵ��ϴ� -> �׻� ����Ǿ���Ѵ� -> ������Ʈ�Ŵ������� ���ְ� ������ Ÿ���� ������Ʈ�Ŵ����� ����.
		//->Ÿ���� ������Ʈ�Ŵ����� �ֱ�� �޸�Ʈ�� �ʹ� ����(������Ʈ�� ��Ÿ�κ��� �ǹ̰� ���� Ÿ���� Ÿ�Ϸ� ���ܵδ°� �浹�� ���� 
		//Ÿ���� ���� ����
		vector<GameObject*> tempInteractList = ObjectManager::GetInstance()->GetClipingInteraceList();
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

void scene1::EnemyRespown(float x, float y)
{
	float RandomZom = Random::GetInstance()->RandomInt(2);
	if (RandomZom == 0)
	{
		Zombie01* zombie01 = new Zombie01(x, y);
		zombie01->SetTileList(mTileList);
		zombie01->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Enemy, zombie01);
	}
	

}
