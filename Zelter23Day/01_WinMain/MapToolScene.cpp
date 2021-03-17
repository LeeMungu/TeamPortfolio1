#include "pch.h"
#include "MapToolScene.h"

#include "Tile.h"
#include "Image.h"
#include "Button.h"
#include "Camera.h"
#include <fstream>
#include "GameObject.h"
#include "Player.h"
#include "InteractObject.h"
#include "NonInteractObject.h"

void MapToolScene::Init()
{
	mTileCountX = 100;
	mTileCountY = 100;
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
				x,
				y,
				0,
				0
			));
			mTileList[y][x]->SetTileLayer(TileLayer::normal);
		}
	}
	
	mCurrentPallete = nullptr;
	mCurrentLayer = TileLayer::normal;
	//-1 = 아직 선택하지 않음을 표시
	mPickStartIndexX = -1;
	mPickStartIndexY = -1;
	mIsExtendTile = false;

	mChangeStartIndexX = -1;
	mChangeStartIndexY = -1;
	mChangeEndIndexX = -1;
	mChangeEndIndexY = -1;
	mIsChangingTile = false;
}

void MapToolScene::Release()
{
	ObjectManager::GetInstance()->Release();

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
		if (PtInRect(&bookRect, _mousePosition))
		{
			//{{ 팔레트 픽~
			vector<vector<Tile*>> palletList = mToolBook->GetPalleteList();
			if (palletList.size() != NULL)
			{
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
			}
			// }}
		}
		else if (!PtInRect(&bookRect, _mousePosition))
		{
			//타일 늘이기
			if (mCurrentPallete == nullptr && !PtInRect(&bookRect, _mousePosition))
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
			//색칠하기 픽
			if (mCurrentPallete != nullptr)
			{
				int indexX = (_mousePosition.x + cameraX) / TileSize;
				int indexY = (_mousePosition.y + cameraY) / TileSize;
				
				mChangeStartIndexX = indexX;
				mChangeStartIndexY = indexY;
			
			}
		}
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
							x,
							y,
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
							i,
							y,
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

			//쭈욱 그리는경우
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
	if (Input::GetInstance()->GetKey(VK_TAB)
		&& mChangeStartIndexX !=-1 && mChangeStartIndexY != -1)
	{
		mIsChangingTile = true;
		int indexX = (_mousePosition.x + cameraX) / TileSize;
		int indexY = (_mousePosition.y + cameraY) / TileSize;
		mChangeEndIndexX = indexX;
		mChangeEndIndexY = indexY;
		
	}
	if (Input::GetInstance()->GetKeyUp(VK_LBUTTON))
	{
		if (mIsChangingTile == true)
		{
			//칠해지는 경우
			//드래그앤드롭으로 칠해지는 경우
			if (mCurrentPallete != nullptr && mIsChangingTile == true
				//책예외
				&& !PtInRect(&bookRect, _mousePosition))
			{
				int minIndexX = 0, maxIndexX = 0;
				int minIndexY = 0, maxIndexY = 0;
				if (mChangeStartIndexX >= mChangeEndIndexX)
				{
					minIndexX = mChangeEndIndexX;
					maxIndexX = mChangeStartIndexX;
				}
				else if (mChangeStartIndexX < mChangeEndIndexX)
				{
					minIndexX = mChangeStartIndexX;
					maxIndexX = mChangeEndIndexX;
				}

				if (mChangeStartIndexY >= mChangeEndIndexY)
				{
					minIndexY = mChangeEndIndexY;
					maxIndexY = mChangeStartIndexY;
				}
				else if (mChangeStartIndexY < mChangeEndIndexY)
				{
					minIndexY = mChangeStartIndexY;
					maxIndexY = mChangeEndIndexY;
				}

				for (int y = minIndexY; y < maxIndexY + 1; ++y)
				{
					for (int x = minIndexX; x < maxIndexX + 1; ++x)
					{

						if (x >= 0 && x < mTileCountX && y >= 0 && y < mTileCountY)
						{
							if (mTileList[y][x]->mImage != mCurrentPallete->mImage ||
								mTileList[y][x]->mFrameIndexX != mCurrentPallete->mFrameIndexX ||
								mTileList[y][x]->mFrameIndexY != mCurrentPallete->mFrameIndexY)
							{
								if (mToolBook->GetIsRoofOn() == true)
								{
									mToolBook->RoofOnMode(x, y);
									mToolBook->SetIsRoofOn(false);
								}
								IBrushTile* command = new IBrushTile(mTileList[y][x], mCurrentPallete);
								PushCommand(command);
								mToolBook->SetIsRoofOn(false);
								//cout << "OnPushCommand" << endl;
							}
							mTileList[y][x]->mTileLayer = mCurrentLayer;
						}

					}
				}
			}
			mIsChangingTile = false;
			mChangeStartIndexX = -1;
			mChangeStartIndexY = -1;
		}
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
		//오브젝트들 제거
		vector<GameObject*> tempMouse = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Mouse);
		if (tempMouse.size() != NULL)
		{
			for (int i = 0; i < tempMouse.size(); ++i)
			{
				tempMouse[i]->SetIsDestroy(true);
			}
		}
	}
	//인터렉트 오브젝트에 따른 타일 속성 바꾸기(wall로 바꿔주기)
	//로드 할때도 해줘야 할듯하다 -> 항상 적용되어야한다 -> 오브젝트매니져에서 해주고 싶지만 타일이 오브젝트매니져에 없다.
	//->타일을 오브젝트매니져에 넣기는 메리트가 너무 적다(업데이트나 기타부분이 의미가 없다 타일은 타일로 남겨두는게 충돌이 적고 
	//타일이 적게 들어갈듯
	vector<GameObject*> tempInteractList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);
	if (tempInteractList.size() != NULL)
	{
		for(int i=0; i<tempInteractList.size();++i)
		{
			//후에 다중 타일 추가로 판정해줘야 한다.
			InteractObject* tempInteract = (InteractObject * )tempInteractList[i];
			int y = 0;
			int countx = tempInteract->GetTileCountX();
			int county = tempInteract->GetTileCountY();
			for (int x = 0;x < countx*county; ++x)
			{
				if (mTileList[tempInteract->GetTileIndexY()-x/countx][tempInteract->GetTileIndexX()+x%countx]->GetTileLayer() != TileLayer::wall)
					mTileList[tempInteract->GetTileIndexY()-x/countx][tempInteract->GetTileIndexX()+x%countx]->SetTileLayer(TileLayer::wall);
			}
			////countx ==1, county ==1 인 경우
			//if(mTileList[tempInteract->GetTileIndexY()][tempInteract->GetTileIndexX()]->GetTileLayer()!= TileLayer::wall)
			//mTileList[tempInteract->GetTileIndexY()][tempInteract->GetTileIndexX()]->SetTileLayer(TileLayer::wall);
			////countx >=2, county ==1 인 경우
			//if (mTileList[tempInteract->GetTileIndexY()][tempInteract->GetTileIndexX()+1]->GetTileLayer() != TileLayer::wall)
			//	mTileList[tempInteract->GetTileIndexY()][tempInteract->GetTileIndexX()+1]->SetTileLayer(TileLayer::wall);
			////countx ==1, county >=2 인 경우
			//if (mTileList[tempInteract->GetTileIndexY()-1][tempInteract->GetTileIndexX()]->GetTileLayer() != TileLayer::wall)
			//	mTileList[tempInteract->GetTileIndexY()-1][tempInteract->GetTileIndexX()]->SetTileLayer(TileLayer::wall);
			////countx >=2, county >=2 인 경우
			//if (mTileList[tempInteract->GetTileIndexY()-1][tempInteract->GetTileIndexX() + 1]->GetTileLayer() != TileLayer::wall)
			//	mTileList[tempInteract->GetTileIndexY()-1][tempInteract->GetTileIndexX() + 1]->SetTileLayer(TileLayer::wall);
		}
	}
}

void MapToolScene::Render(HDC hdc)
{
	Camera* mainCamera = CameraManager::GetInstance()->GetMainCamera();

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
	D2DRenderer::GetInstance()
		->RenderText(10, 160, L"TAP + 드래그엔드롭 : 범위그려줌", 12);
	D2DRenderer::GetInstance()
		->RenderText(10, 190, L"BackSpace : 마우스 초기화", 12);

	//클릭한 속성별로 마우스 따라다니며 그려주기
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

	//드래그시 랙트 그려주기
	if (mIsChangingTile == true
		&& mChangeStartIndexX != -1 && mChangeStartIndexY !=-1
		&& mChangeEndIndexX!=-1 && mChangeEndIndexY != -1)
	{
		int minIndexX = 0, maxIndexX = 0;
		int minIndexY = 0, maxIndexY = 0;
		if (mChangeStartIndexX >= mChangeEndIndexX)
		{
			minIndexX = mChangeEndIndexX;
			maxIndexX = mChangeStartIndexX;
		}
		else if (mChangeStartIndexX < mChangeEndIndexX)
		{
			minIndexX = mChangeStartIndexX;
			maxIndexX = mChangeEndIndexX;
		}

		if (mChangeStartIndexY >= mChangeEndIndexY)
		{
			minIndexY = mChangeEndIndexY;
			maxIndexY = mChangeStartIndexY;
		}
		else if (mChangeStartIndexY < mChangeEndIndexY)
		{
			minIndexY = mChangeStartIndexY;
			maxIndexY = mChangeEndIndexY;
		}
		RECT rc = { mTileList[minIndexY][minIndexX]->GetRect().left,mTileList[minIndexY][minIndexX]->GetRect().top,
			mTileList[maxIndexY][maxIndexX]->GetRect().right, mTileList[maxIndexY][maxIndexX]->GetRect().bottom };
		//Gizmo::GetInstance()->DrawRect(hdc, rc, Gizmo::Color::Blue);
		CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, rc);
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
		//타일 갯수 저장
		saveStream << mTileCountX;
		saveStream << ',';
		saveStream << mTileCountY;
		saveStream << endl;
		//타일각각마다 저장
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
		//오브젝트레이어 구분, 갯수 <- *없으면 아에 기록도 하지 않는다.
		int intObjectLayer = (int)ObjectLayer::HousingObject;
		vector<GameObject*> tempObject = ObjectManager::GetInstance()->GetObjectList((ObjectLayer)intObjectLayer);
		
		saveStream << intObjectLayer;
		saveStream << ',';
		saveStream << tempObject.size();
		saveStream << endl;
		if (tempObject.size() != NULL)
		{	
			//각 오브젝트레이어의 이미지키, x좌표, y좌표
			for (int i = 0; i < tempObject.size(); ++i)
			{
				//집은 어떻게 저장할지 더 생각해봐야한다...
				//saveStream << (HousingObject*)tempObject[i]->
			}
		}
		//인터랙트오브젝트레이어 구분, 갯수
		intObjectLayer = (int)ObjectLayer::InteractObject;
		tempObject.clear();
		tempObject = ObjectManager::GetInstance()->GetObjectList((ObjectLayer)intObjectLayer);
		
			saveStream << intObjectLayer;
			saveStream << ',';
			saveStream << tempObject.size();
			saveStream << endl;
		if (tempObject.size() != NULL)
		{
			//각 오브젝트레이어의 이미지키, x좌표, y좌표
			for (int i = 0; i < tempObject.size(); ++i)
			{
				wstring imagekey;
				string str;
				imagekey = ((InteractObject*)tempObject[i])->GetImageKey();
				str.assign(imagekey.begin(), imagekey.end());
				saveStream << str;
				saveStream << ",";
				saveStream << tempObject[i]->GetX();
				saveStream << ",";
				saveStream << ((InteractObject*)tempObject[i])->GetInputY();
				saveStream << ",";
				saveStream << ((InteractObject*)tempObject[i])->GetHp();
				saveStream << ",";
				saveStream << ((InteractObject*)tempObject[i])->GetTileCountX();
				saveStream << ",";
				saveStream << ((InteractObject*)tempObject[i])->GetTileCountY();
				saveStream << endl;
			}
		}
		//언인터랙트오브젝트레이어 구분, 갯수
		intObjectLayer = (int)ObjectLayer::NoninteractObject;
		tempObject.clear();
		tempObject = ObjectManager::GetInstance()->GetObjectList((ObjectLayer)intObjectLayer);
		
		saveStream << intObjectLayer;
		saveStream << ',';
		saveStream << tempObject.size();
		saveStream << endl;
		if (tempObject.size() != NULL)
		{
			//각 오브젝트레이어의 이미지키, x좌표, y좌표
			for (int i = 0; i < tempObject.size(); ++i)
			{
				wstring imagekey;
				string str;
				imagekey = ((NonInteractObject*)tempObject[i])->GetImageKey();
				str.assign(imagekey.begin(), imagekey.end());
				saveStream << str;
				saveStream << ",";
				saveStream << tempObject[i]->GetX();
				saveStream << ",";
				saveStream << tempObject[i]->GetY();
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
				getline(loadStream, buffer, ',');
				imageKey.assign(buffer.begin(), buffer.end());
				getline(loadStream, buffer, ',');
				x = stoi(buffer);
				getline(loadStream, buffer);
				y = stoi(buffer);
				//하우징 생성 <-추후에 밑에 예같이 생성해줄예정
				// 생성자 매개변수는 더 늘릴 예정?
				//HousingObject* temp = new HousingObject(imageKey, x, y);
				//temp->Init();
				//ObjectManager::GetInstance()->AddObject(objectLayer, temp);
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
		//인터렉트 오브젝트에 따른 타일 속성 바꾸기(wall로 바꿔주기)
		//로드 할때도 해줘야 할듯하다 -> 항상 적용되어야한다 -> 오브젝트매니져에서 해주고 싶지만 타일이 오브젝트매니져에 없다.
		//->타일을 오브젝트매니져에 넣기는 메리트가 너무 적다(업데이트나 기타부분이 의미가 없다 타일은 타일로 남겨두는게 충돌이 적고 
		//타일이 적게 들어갈듯
		vector<GameObject*> tempInteractList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);
		if (tempInteractList.size() != NULL)
		{
			for (int i = 0; i < tempInteractList.size(); ++i)
			{
				//후에 다중 타일 추가로 판정해줘야 한다.
				InteractObject* tempInteract = (InteractObject*)tempInteractList[i];
				if (mTileList[tempInteract->GetTileIndexY()][tempInteract->GetTileIndexX()]->GetTileLayer() != TileLayer::wall)
					mTileList[tempInteract->GetTileIndexY()][tempInteract->GetTileIndexX()]->SetTileLayer(TileLayer::wall);
				if (tempInteract->GetTileCountX() == 2)
				{
					if (mTileList[tempInteract->GetTileIndexY()][tempInteract->GetTileIndexX()+1]->GetTileLayer() != TileLayer::wall)
						mTileList[tempInteract->GetTileIndexY()][tempInteract->GetTileIndexX()+1]->SetTileLayer(TileLayer::wall);
				}
				if (tempInteract->GetTileCountY() == 2)
				{
					if (mTileList[tempInteract->GetTileIndexY() - 1][tempInteract->GetTileIndexX()]->GetTileLayer() != TileLayer::wall)
						mTileList[tempInteract->GetTileIndexY() - 1][tempInteract->GetTileIndexX()]->SetTileLayer(TileLayer::wall);
				}
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

