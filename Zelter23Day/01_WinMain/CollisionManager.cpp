#include "pch.h"
#include "CollisionManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "GameObject.h"


void CollisionManager::Update()
{
	PlayerCollion();
	PlayerTakenZombie();
}

void CollisionManager::PlayerCollion()
{

}

void CollisionManager::PlayerTakenZombie()
{
	float invincibleCount = mPlayer->GetInvincibleCount();
	RECT temp;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	RECT playerRC = mPlayer->GetRect();
	RECT enemyRC;
	vector<GameObject*> zombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	for (int i = 0; i < zombie.size(); ++i)
	{
		enemyRC = zombie[i]->GetRect();
		if (IntersectRect(&temp, &playerRC, &enemyRC))
		{
			if (mPlayer->GetIsInvincible() == false) //플레이어 HP 변동
			{
				mPlayer->SetNoDamage(true);
				mPlayer->SetHP(mPlayer->GetHP() - 1);				
			}


			//플레이어 좀비 충돌 처리
			float pX = mPlayer->GetX();
			float pY = mPlayer->GetY();
			float pSizeX = mPlayer->GetSizeX();
			float pSizeY = mPlayer->GetSizeY();

			float tempW = temp.right - temp.left;
			float tempH = temp.bottom - temp.top;
			float tempX = temp.left + tempW / 2;
			float tempY = temp.top + tempW / 2;
			float enemyX = enemyRC.left + (enemyRC.right - enemyRC.left) / 2;
			float enemyY = enemyRC.top + (enemyRC.bottom - enemyRC.top) / 2;

			if (tempW < tempH && tempX > enemyX && playerRC.left < enemyRC.right)
			{
				pX = enemyRC.right + pSizeX / 2;
			}
			if (tempW < tempH && tempX < enemyX && playerRC.right > enemyRC.left)
			{
				pX = enemyRC.left - pSizeX / 2;
			}
			if (tempW > tempH && tempY > enemyY && playerRC.top < enemyRC.bottom)
			{
				pY = enemyRC.bottom + pSizeY / 2;
			}
			if (tempW > tempH && tempY < enemyY && playerRC.bottom > enemyRC.top)
			{
				pY = enemyRC.top - pSizeY / 2;
			}

			mPlayer->SetX(pX);
			mPlayer->SetY(pY);

		}
	}
	if (mPlayer->GetInvincibleCount()==false)
	{
		invincibleCount += Time::GetInstance()->DeltaTime();
	}
	if (invincibleCount <= 0.3f && mPlayer->GetIsInvincible()==true)
	{
		
	}
	if (invincibleCount > 1.5)
	{
		invincibleCount = 0;
		mPlayer->SetNoDamage(true);
	}

}

void CollisionManager::knockback()
{
}
