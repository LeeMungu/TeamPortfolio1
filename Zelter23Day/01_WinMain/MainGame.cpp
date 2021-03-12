#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include "MapToolScene.h"
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
	
	//�� �̹���
	IMAGEMANAGER->LoadFromFile(L"House", Resources(L"/02_House/House01_INSIDE_BMP.bmp"),9,9);
	IMAGEMANAGER->LoadFromFile(L"HouseRoof", Resources(L"/02_House/House01_Roof_bmp.bmp"),9,9);

	SceneManager::GetInstance()->AddScene(L"MapToolScene", new MapToolScene);
	SceneManager::GetInstance()->AddScene(L"Scene1", new scene1);
	SceneManager::GetInstance()->LoadScene(L"MapToolScene");
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

	TextOut(hdc, 10, 10, strWorldTime.c_str(), strWorldTime.length());
	TextOut(hdc, 10, 25, strDeltaTime.c_str(), strDeltaTime.length());
	TextOut(hdc, 10, 40, strFPS.c_str(), strFPS.length());
}

