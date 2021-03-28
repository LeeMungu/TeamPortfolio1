#include "pch.h"
#include "MainGame.h"

#include "Image.h"
#include "MapToolLoadingScene.h"
#include "MapToolScene.h"
#include "LoadingScene.h"
#include "MainScene.h"
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

	RECT Clip;
	GetClientRect(_hWnd, &Clip);
	ClientToScreen(_hWnd, (LPPOINT)&Clip);
	ClientToScreen(_hWnd, (LPPOINT)(&Clip.right));
	ClipCursor(&Clip);



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
	
	//�ε�ȭ��
	ImageManager::GetInstance()->LoadFromFile(L"PrologueImage1", Resources(L"PrologueImage.png"));
	ImageManager::GetInstance()->LoadFromFile(L"PrologueImage2", Resources(L"PrologueImage2.png"));
	ImageManager::GetInstance()->LoadFromFile(L"LoadingCat", Resources(L"LoadingImage1.png"));
	ImageManager::GetInstance()->LoadFromFile(L"LoadingImage2", Resources(L"LoadingImage-1.png"));
	SoundPlayer::GetInstance()->LoadFromFile(L"Siren1", Resources(L"/09_Sound/Siren1.mp3"), false);
	SoundPlayer::GetInstance()->LoadFromFile(L"KakaoTalkSound", Resources(L"/09_Sound/KakaoTalkSound.mp3"), false);
	//�ؽ�Ʈ �ڽ�
	ImageManager::GetInstance()->LoadFromFile(L"TextBox", Resources(L"TextBox.png"));
	//��ȭ��
	ImageManager::GetInstance()->LoadFromFile(L"EveningBackground", Resources(L"EveningBackground.png"));
	//���̹���
	ImageManager::GetInstance()->LoadFromFile(L"Rain", Resources(L"Rain.png"));

	SceneManager::GetInstance()->AddScene(L"MapToolLoadingScene", new MapToolLoadingScene);
	SceneManager::GetInstance()->AddScene(L"MapToolScene", new MapToolScene);
	SceneManager::GetInstance()->AddScene(L"LoadingScene", new LoadingScene);
	SceneManager::GetInstance()->AddScene(L"Scene1", new scene1);
	SceneManager::GetInstance()->AddScene(L"MainScene", new MainScene);
	SceneManager::GetInstance()->LoadScene(L"MainScene");
	//SceneManager::GetInstance()->LoadScene(L"MapToolLoadingScene");
	//SceneManager::GetInstance()->LoadScene(L"LoadingScene");

	//���� Ÿ�ٰ� �ٸ� ����Ÿ�� ����
	D2DRenderer::GetInstance()->GetRenderTarget()->CreateCompatibleRenderTarget(&mFirstBuffer);
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

	if (Input::GetInstance()->GetKeyDown(VK_F1))
	{
		RECT Clip;
		GetClientRect(_hWnd, &Clip);
		ClientToScreen(_hWnd, (LPPOINT)&Clip);
		ClientToScreen(_hWnd, (LPPOINT)(&Clip.right));
		ClipCursor(&Clip);
	}
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
		////�ΰ��ӷ����� ����
		//mFirstBuffer->BeginDraw();
		//mFirstBuffer->Clear();
		{
			SceneManager::GetInstance()->Render(hdc);
			RenderTime(hdc);
		}
		//mFirstBuffer->EndDraw();

		//// {{ ��ó�� ���� :: ȭ�� ��ü�� ����ũ�� �÷� ��Ƽ�� ����
		//ID2D1RenderTarget* renderTarget = D2DRenderer::GetInstance()->GetRenderTarget();
		//ID2D1SolidColorBrush* brush;
		//renderTarget->CreateSolidColorBrush(D2D1::ColorF(0.2f, 0, 0.3f, 0.2f), &brush);
		//
		//ID2D1Bitmap* bitmap;
		//mFirstBuffer->GetBitmap(&bitmap);
		//D2D1_RECT_F dxArea = D2D1::RectF(0.f, 0.f, WINSIZEX, WINSIZEY);
		//
		//renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		//renderTarget->DrawBitmap(bitmap, dxArea, 1.0f);
		////�׷ȴ� ���� ����� Multiply �ؼ� ����ۿ� ������
		//renderTarget->FillOpacityMask(bitmap, brush, D2D1_OPACITY_MASK_CONTENT::D2D1_OPACITY_MASK_CONTENT_GRAPHICS, dxArea, dxArea);
		//brush->Release();
		//// }} 
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

