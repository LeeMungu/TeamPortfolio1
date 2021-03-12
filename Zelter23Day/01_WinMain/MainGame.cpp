#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include "MapToolScene.h"
#include "LoadingScene.h"
#include "scene1.h"
#include "Camera.h"

#define SizeUp 3
/*
Initialize : �ʱ�ȭ
������ ������ �����ϱ� ���� �ʱ�ȭ �� ������ ���⼭ ����
���� �����ϱ� ���� �� �ѹ��� ����Ǵ� �Լ�
*/
void MainGame::Init()
{
	Camera* main = new Camera();
	main->Init();
	CameraManager::GetInstance()->SetMainCamera(main);

	ImageManager::GetInstance()->LoadFromFile(L"Book", Resources(L"book.png"), 9, 5);
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

	//�� �̹���
	IMAGEMANAGER->LoadFromFile(L"House", Resources(L"/02_House/House01_INSIDE_1.png"),9,9);
	IMAGEMANAGER->LoadFromFile(L"HouseRoof", Resources(L"/02_House/House01_Roof_1.png"),9,9);
	IMAGEMANAGER->LoadFromFile(L"Zombie01", Resources(L"/06_Zombie/Zombie01.png"), 10, 2);

	SceneManager::GetInstance()->AddScene(L"MapToolScene", new MapToolScene);
	SceneManager::GetInstance()->AddScene(L"LoadingScene", new LoadingScene);
	SceneManager::GetInstance()->AddScene(L"Scene1", new scene1);
	SceneManager::GetInstance()->LoadScene(L"LoadingScene");
}

/*
Release : �޸� ������ �� �ҷ��ִ� �Լ�
����Ƽ��� OnDestroy
�ش� Ŭ���� �ν��Ͻ��� �޸� ���� �� �� �� �ѹ� ȣ�����ִ� �༮
*/
void MainGame::Release()
{
	Random::ReleaseInstance();	//�̱��� �ν��Ͻ� ����
}

/*
Update : �� ������ ����Ǵ� �Լ�, ���⼭ ���� ó�� �Ѵ�.
*/
void MainGame::Update()
{
	SceneManager::GetInstance()->Update();
}

/*
Render : �� ������ ����Ǵ� �Լ�, Update�� ������ Render�� ����ȴ�.
ȭ�鿡 �׷��ִ� �͵��� ���� ���⼭ ó��

�Ű����� hdc : ������ â�� HDC�� ����
*/
void MainGame::Render(HDC hdc)
{
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	//�� �ȿ��� �׷���
	{
		SceneManager::GetInstance()->Render(hdc);
		//RenderTime(backDC);
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

	D2DRenderer::GetInstance()
		->RenderText(10, 10, strWorldTime.c_str(),strWorldTime.length());
	TextOut(hdc, 10, 25, strDeltaTime.c_str(), strDeltaTime.length());
	TextOut(hdc, 10, 40, strFPS.c_str(), strFPS.length());
}

