#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include "MapToolLoadingScene.h"
#include "MapToolScene.h"
#include "LoadingScene.h"
#include "scene1.h"
#include "Camera.h"

#define SizeUp 3
/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
*/
void MainGame::Init()
{
	Camera* main = new Camera();
	main->Init();
	CameraManager::GetInstance()->SetMainCamera(main);

	ImageManager::GetInstance()->LoadFromFile(L"Book", Resources(L"book.png"), 9, 5);
	ImageManager::GetInstance()->LoadFromFile(L"BookButton", Resources(L"bookUI.png"), 3, 4);
	ImageManager::GetInstance()->LoadFromFile(L"Tile", Resources(L"tiletest.bmp"), 8, 4);
	ImageManager::GetInstance()->LoadFromFile(L"Tile1", Resources(L"04_Tile/Tile (1).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile2", Resources(L"04_Tile/Tile (2).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile3", Resources(L"04_Tile/Tile (3).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile4", Resources(L"04_Tile/Tile (4).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile5", Resources(L"04_Tile/Tile (5).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile6", Resources(L"04_Tile/Tile (6).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile7", Resources(L"04_Tile/Tile (7).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile8", Resources(L"04_Tile/Tile (8).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile9", Resources(L"04_Tile/Tile (9).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile10", Resources(L"04_Tile/Tile (10).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile11", Resources(L"04_Tile/Tile (11).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile12", Resources(L"04_Tile/Tile (12).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile13", Resources(L"04_Tile/Tile (13).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile14", Resources(L"04_Tile/Tile (14).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile15", Resources(L"04_Tile/Tile (15).png"), 8, 8);
	ImageManager::GetInstance()->LoadFromFile(L"Tile16", Resources(L"04_Tile/Tile (16).png"), 3, 7);


	//집 이미지
	IMAGEMANAGER->LoadFromFile(L"House", Resources(L"/02_House/House01_INSIDE_1.png"),9,9);
	IMAGEMANAGER->LoadFromFile(L"HouseRoof", Resources(L"/02_House/House01_Roof_1.png"),9,9);

	SceneManager::GetInstance()->AddScene(L"MapToolLoadingScene", new MapToolLoadingScene);
	SceneManager::GetInstance()->AddScene(L"MapToolScene", new MapToolScene);
	SceneManager::GetInstance()->AddScene(L"LoadingScene", new LoadingScene);
	SceneManager::GetInstance()->AddScene(L"Scene1", new scene1);
	SceneManager::GetInstance()->LoadScene(L"LoadingScene");
	//SceneManager::GetInstance()->LoadScene(L"MapToolLoadingScene");
}

/*
Release : 메모리 해제할 때 불러주는 함수
유니티라면 OnDestroy
해당 클래스 인스턴스가 메모리 해제 될 때 단 한번 호출해주는 녀석
*/
void MainGame::Release()
{
	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제
}

/*
Update : 매 프레임 실행되는 함수, 여기서 연산 처리 한다.
*/
void MainGame::Update()
{
	SceneManager::GetInstance()->Update();
}

/*
Render : 매 프레임 실행되는 함수, Update가 끝나고 Render가 실행된다.
화면에 그려주는 것들은 전부 여기서 처리

매개변수 hdc : 윈도우 창의 HDC가 들어옴
*/
void MainGame::Render(HDC hdc)
{
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	//이 안에서 그려라
	{
		SceneManager::GetInstance()->Render(hdc);
		RenderTime(hdc);
	}
	D2DRenderer::GetInstance()->EndRender();
}

void MainGame::RenderTime(HDC hdc)
{
	float worldTime = Time::GetInstance()->GetWorldTime();
	float deltaTime = Time::GetInstance()->DeltaTime();
	ULONG fps = Time::GetInstance()->GetmFrameRate();
	wstring strWorldTime = L"WorldTime : " + to_wstring(worldTime);
	wstring strDeltaTime = L"DeltaTime : " + to_wstring(deltaTime);
	wstring strFPS = L"FPS : " + to_wstring(fps);

	//D2DRenderer::GetInstance()
	//	->RenderText(10, 150, strWorldTime.c_str(),20);
	//D2DRenderer::GetInstance()
	//	->RenderText(10, 180, strDeltaTime.c_str(), 20);
	D2DRenderer::GetInstance()
		->RenderText(10, 250, strFPS.c_str(), 20);
}

