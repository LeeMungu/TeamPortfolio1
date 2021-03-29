#include "pch.h"
#include "Weapon.h"
#include "Image.h"
#include "Tile.h"
#include "MapToolScene.h"
#include "Camera.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "WorkTable.h"


Weapon::Weapon(const string& name, const float x, float y, int imageX, int imageY)
	:GameObject(name)
{
	mX = x;
	mY = y;
	mImage = IMAGEMANAGER->FindImage(L"Weapon_pistol");
	mSizeX = mImage->GetFrameWidth()*2;
	mSizeY = mImage->GetFrameHeight()*2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mImageX = imageX;
	mImageY = imageY;
}

void Weapon::Init()
{
	mStartImageX = mImageX;
	mStartImageY = mImageY;
	mStartX = mX;
	mStartY = mY;
	mAngle = 0.f;
	mAngle2 = 0.2f;
	mAngle3 = 0.3f;

	mRect = RectMake(mX, mY, mSizeX, mSizeY);
	mIsUse = true;
}

void Weapon::Release()
{
}

void Weapon::Update()
{
	float cameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	float cameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;

	mX = mPlayer->GetRect().left + 50;
	mY = mPlayer->GetRect().top;

	mAngle = -(Math::GetAngle(_mousePosition.x + cameraX, _mousePosition.y + cameraY, mX, mY)) / PI * 180.f;
	mAngle2 = -(Math::GetAngle(_mousePosition.x + cameraX, _mousePosition.y + cameraY, mX, mY)) / PI * 181.f;
	mAngle3 = -(Math::GetAngle(_mousePosition.x + cameraX, _mousePosition.y + cameraY, mX, mY)) / PI * 182.f;
	mAngle4 = -(Math::GetAngle(_mousePosition.x + cameraX, _mousePosition.y + cameraY, mX, mY)) / PI * 183.f;
	mAngle5 = -(Math::GetAngle(_mousePosition.x + cameraX, _mousePosition.y + cameraY, mX, mY)) / PI * 184.f;

	mRect = RectMake(mX, mY, mSizeX, mSizeY);

	if (mIsUse)
	{
		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		{
			if ((Inventory*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Inventory") != NULL)
			{

				if (((Inventory*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "Inventory"))->GetOpened() == true)
				{

				}
				else
				{
					Bullet* bullet = new Bullet(mX, mY, -mAngle * PI / 180.f);
					bullet->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet);

					if (mName == "Shotgun")
					{
						Bullet* bullet2 = new Bullet(mX, mY, -mAngle2 * PI / 183.f);
						bullet2->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet2);

						Bullet* bullet3 = new Bullet(mX, mY, -mAngle3 * PI / 185.f);
						bullet3->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet3);

						Bullet* bullet4 = new Bullet(mX, mY, -mAngle4 * PI / 188.f);
						bullet4->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet4);

						Bullet* bullet5 = new Bullet(mX, mY, -mAngle5 * PI / 191.f);
						bullet5->Init();
						ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet5);
					}

					SoundPlayer::GetInstance()->Play(L"ShotSound", 0.5f
						* SoundPlayer::GetInstance()->GetEffectVolume());
				}
			}
			else
			{
				Bullet* bullet = new Bullet(mX, mY, -mAngle * PI / 180.f);
				bullet->Init();
				ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet);

				if (mName == "Shotgun")
				{
					Bullet* bullet2 = new Bullet(mX, mY, -mAngle2 * PI / 183.f);
					bullet2->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet2);

					Bullet* bullet3 = new Bullet(mX, mY, -mAngle3 * PI / 185.f);
					bullet3->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet3);

					Bullet* bullet4 = new Bullet(mX, mY, -mAngle4 * PI / 188.f);
					bullet4->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet4);

					Bullet* bullet5 = new Bullet(mX, mY, -mAngle5 * PI / 191.f);
					bullet5->Init();
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Bullet, bullet5);
				}

				SoundPlayer::GetInstance()->Play(L"ShotSound", 0.5f
					* SoundPlayer::GetInstance()->GetEffectVolume());
			}
		}
	}
	
}

void Weapon::Render(HDC hdc)
{
	//mImage->SetAngle(mAngle);
	//CameraManager::GetInstance()->GetMainCamera()
	//	->ScaleFrameRender(hdc, mImage, mRect.left,mRect.top, mImageX, mImageY, mSizeX, mSizeY);
}
