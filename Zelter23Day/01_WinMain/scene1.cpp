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

//밤
#include "Evening.h"
//이벤트
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

	//밤
	Evening* evening = new Evening();
	ObjectManager::GetInstance()->AddObject(ObjectLayer::Weater, evening);

	Load();

	ItemManager::GetInstance()->Init();
	ObjectManager::GetInstance()->Init();
	CollisionManager::GetInstance()->Init();
	camera->ChangeMode(Camera::Mode::Follow);

	//true 설정하면 씬 시간 흐름
	Time::GetInstance()->SetIsSceneStart(true);
	mZombieCount = 100;
	mZombieCoolTime = 1; // 좀비 쿨타임
	mZombieCoolTimer = 0;//델타타임 더해줄 타이머

	SoundPlayer::GetInstance()->Play(L"BGM", 0.5f * SoundPlayer::GetInstance()->GetBgmVolume());
	SoundPlayer::GetInstance()->Play(L"ForestSound", 0.2f * SoundPlayer::GetInstance()->GetBgmVolume());
	SoundPlayer::GetInstance()->Stop(L"Siren1");

	//이벤트 초기화 
	GameEventManager::GetInstance()->RemoveAllEvent();
	//패스파인더에서 터짐 후에 수정예정
	//for (int i = 0; i < 1; ++i)
	//{
	//	GameEventManager::GetInstance()->PushEvent(new IZombiGeneration(1000, 1600, mTileList));
	//}
	//첫 등장 시 텍스트 창 출력
	GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
	GameEventManager::GetInstance()->PushEvent(new IDelayEvent(0.5f));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"성남시에 군인들이\n아직 있다고들었어.\n길을 따라 남동쪽으로 가보자."));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(4.f, L"다들 살아있으면 좋을텐데.\n좀비들이 점점 남쪽으로\n내려오는 모양이야."));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(4.f, L"혹시 가는 길에 있는 경찰서에서\n권총을 주울 수 있을지 몰라."));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(4.f, L"우선 가지고 있는 도끼로\n녀석들을 상대하자."));
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"좀비에 접근 후 F키를 누르면\n좀비를 공격할 수 있습니다."));
	GameEventManager::GetInstance()->PushEvent(new IAllUnitActive());

	//특정 장소 도착 시 좀비등장 및 공격 텍스트창 출력
	GameEventManager::GetInstance()->PushEvent(new ITileEvent(ITileEvent::Mode::DownRight,TileSize*84,TileSize*125));
	GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
	GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"이 길을 따라가면 성남이야."));
	GameEventManager::GetInstance()->PushEvent(new IAllUnitActive());

	//탈출 전 폭탄 제작 이벤트 안내 텍스트창 출력
	GameEventManager::GetInstance()->
		PushEvent(new IObjectCrushEvent(
			ObjectManager::GetInstance()->FindObject(ObjectLayer::InteractObject, "Barricade2"),
			ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player")));
	
		GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"성남으로 가려면 이쪽으로\n가야하는데 길이 막혀있다..."));
		GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f));
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"아마 사제폭탄으로\n길을 만들 수 있을거야."));
		GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f));
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"주변을 돌아다니면서\n재료를 모아보자."));
		GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f));
		GameEventManager::GetInstance()->PushEvent(new IAllUnitActive());
	
		//좀비 등장 이벤트
		
		GameEventManager::GetInstance()->PushEvent(new ITileEvent(ITileEvent::Mode::UpRight, TileSize * 232, TileSize * 68));
		GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"표지판에 누군가가 급하게\n휘갈겨 쓴 메모가 보인다."));
		GameEventManager::GetInstance()->PushEvent(new IDelayEvent(1.f));
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"공터에 겨우 좀비들을\n몰아넣었으니 녀석들을\n유인하는 행동을 하지말 것\n목숨책임안짐."));
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


		//폭발 후 엔딩
		GameEventManager::GetInstance()->PushEvent(new ITileEvent(ITileEvent::Mode::UpRight, TileSize * 267, TileSize * 114));
		GameEventManager::GetInstance()->PushEvent(new IAllUnitStop());
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(3.f, L"좋아 이제 가볼까."));
		GameEventManager::GetInstance()->PushEvent(new ITextEvent(5.f, L"다들 무사해줘."));
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
	//알아서해
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
	
	//이벤트
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


	//타일속성 바꿔주기전에 초기화해주기
	//카메라에 맞춰서 타일을 그려줌
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
	//인터렉트 오브젝트에 따른 타일 속성 바꾸기(wall로 바꿔주기)
	//로드 할때도 해줘야 할듯하다 -> 항상 적용되어야한다 -> 오브젝트매니져에서 해주고 싶지만 타일이 오브젝트매니져에 없다.
	//->타일을 오브젝트매니져에 넣기는 메리트가 너무 적다(업데이트나 기타부분이 의미가 없다 타일은 타일로 남겨두는게 충돌이 적고 
	//타일이 적게 들어갈듯
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
	//집벽 타일 처리
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

	//카메라에 맞춰서 타일을 그려줌
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
			//이벤트 테스팅용 지우지 말것!
			//CameraManager::GetInstance()->GetMainCamera()->RenderText(
			//	mTileList[y][x]->GetX(), mTileList[y][x]->GetY(),
			//	to_wstring(x)+L","+ to_wstring(y),
			//	10);
		}
	}

	//TextOut(hdc, 10, 10, to_wstring(renderCount).c_str(), to_wstring(renderCount).length());

	ObjectManager::GetInstance()->Render(hdc);
	//씬 시간 보기
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
		//오브젝트들 제거
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

		//오브젝트 읽어오기
		string bufferObjectLayer;//레이어
		//집 읽어오기
		getline(loadStream, bufferObjectLayer, ',');
		string buffer;
		ObjectLayer objectLayer = (ObjectLayer)stoi(bufferObjectLayer);
		getline(loadStream, buffer);
		int objectSize = stoi(buffer);
		//레이어, 갯수
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
				//하우징 생성 <-추후에 밑에 예같이 생성해줄예정
				// 생성자 매개변수는 더 늘릴 예정?
				HousingObject* temp = new HousingObject(imageKey, x, y, tileCountX, tileCountY);
				temp->Init();
				ObjectManager::GetInstance()->AddObject(objectLayer, temp);
			}
		}
		//인터렉트 읽어오기
		getline(loadStream, bufferObjectLayer, ',');
		objectLayer = (ObjectLayer)stoi(bufferObjectLayer);
		getline(loadStream, buffer);
		objectSize = stoi(buffer);
		//레이어, 갯수
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
				//위에서 인터렉트인것을 확인했으므로 임의로 넣는다
				//생성
				InteractObject* temp = new InteractObject(imageKey, x, y, hp, tileCountX, tileCountY);
				temp->Init();
				ObjectManager::GetInstance()->AddObject(objectLayer, temp);
			}
		}
		//언인터렉트 읽어오기
		getline(loadStream, bufferObjectLayer, ',');
		//순서는-하우스, 인터렉트, 언인터렉트	
		objectLayer = (ObjectLayer)stoi(bufferObjectLayer);
		getline(loadStream, buffer);
		objectSize = stoi(buffer);
		//레이어, 갯수
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
				//위에서 언인터렉트인것을 확인했으므로 임의로 넣는다
				//생성
				NonInteractObject* temp = new NonInteractObject(imageKey, x, y);
				temp->Init();
				ObjectManager::GetInstance()->AddObject(objectLayer, temp);
			}
		}
		//타일속성 바꿔주기전에 초기화해주기
		//카메라에 맞춰서 타일을 그려줌
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
		//인터렉트 오브젝트에 따른 타일 속성 바꾸기(wall로 바꿔주기)
		//로드 할때도 해줘야 할듯하다 -> 항상 적용되어야한다 -> 오브젝트매니져에서 해주고 싶지만 타일이 오브젝트매니져에 없다.
		//->타일을 오브젝트매니져에 넣기는 메리트가 너무 적다(업데이트나 기타부분이 의미가 없다 타일은 타일로 남겨두는게 충돌이 적고 
		//타일이 적게 들어갈듯
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
