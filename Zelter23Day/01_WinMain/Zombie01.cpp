#include "pch.h"
#include "Zombie01.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"
#include "Camera.h"

void Zombie01::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Player_run");
}

void Zombie01::Release()
{
}

void Zombie01::Update()
{
}

void Zombie01::Render(HDC hdc)
{
}

void Zombie01::Patrol()
{
}

void Zombie01::SearchPlayer()
{
}

void Zombie01::Attack()
{
}
