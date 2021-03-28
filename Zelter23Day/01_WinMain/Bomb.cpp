#include "pch.h"
#include "Bomb.h"
#include "Image.h"
#include "Camera.h"
#include "ObjectManager.h"
#include "Inventory.h"
#include "WorkTable.h"


void Bomb::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Bomb");
	mSizeX = mImage->GetFrameWidth() * 2;
	mSizeY = mImage->GetFrameHeight() * 2;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mIsExplosion = false;

	mIsUse = true;

	SoundPlayer::GetInstance()->Play(L"BombSound", 0.8 * SoundPlayer::GetInstance()->GetEffectVolume());

}

void Bomb::Release()
{

}

void Bomb::Update()
{
	float cameraX = CameraManager::GetInstance()->GetMainCamera()->GetRect().left;
	float cameraY = CameraManager::GetInstance()->GetMainCamera()->GetRect().top;
	//��...�������ƴ�...

	if (mIsUse == true)
	{
		if (Input::GetInstance()->GetKeyDown('B'))
		{
			SoundPlayer::GetInstance()->Play(L"BombSound", 0.8 
				* SoundPlayer::GetInstance()->GetEffectVolume());

		}
	}



}

void Bomb::Render(HDC hdc)
{
}
