#include "pch.h"
#include "CollisionManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "InteractObject.h"
#include "Enemy.h"


void CollisionManager::Init()
{
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
}

void CollisionManager::Update()
{
	ObjectCollision();
	PlayerPhysics();
	PlayerTakenDamaged();
}


void CollisionManager::ObjectCollision()
{
	RECT temp;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	if (mPlayer != nullptr)
	{
		RECT playerRC = mPlayer->GetCollisionBox();
		RECT ObjectRC;
		vector<GameObject*> object = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);
		if (object.size() != NULL)
		{
			for (int i = 0; i < object.size(); ++i)
			{
				ObjectRC = ((InteractObject*)object[i])->GetInteractRect();
				if (IntersectRect(&temp, &playerRC, &ObjectRC))	//플레이어 충돌박스와 오브젝트 충돌
				{
					float pX = mPlayer->GetX();
					float pY = mPlayer->GetY();
					float pSizeX = playerRC.bottom - playerRC.top;
					float pSizeY = playerRC.right - playerRC.left;

					float tempW = temp.right - temp.left;
					float tempH = temp.bottom - temp.top;
					float tempX = temp.left + tempW / 2;
					float tempY = temp.top + tempH / 2;
					float ObjectX = ObjectRC.left + (ObjectRC.right - ObjectRC.left) / 2;
					float ObjectY = ObjectRC.top + (ObjectRC.bottom - ObjectRC.top) / 2;

					if (tempW < tempH && tempX > ObjectX && playerRC.left <= ObjectRC.right)
					{
						pX = ObjectRC.right + pSizeX / 2;
					}
					if (tempW < tempH && tempX < ObjectX && playerRC.right >= ObjectRC.left)
					{
						pX = ObjectRC.left - pSizeX / 2;
					}
					if (tempW > tempH && tempY > ObjectY && playerRC.top <= ObjectRC.bottom)
					{
						pY = ObjectRC.bottom + pSizeY / 2 ;
					}
					if (tempW > tempH && tempY < ObjectY && playerRC.bottom >= ObjectRC.top)
					{
						pY = ObjectRC.top - pSizeY / 2;
					}

					mPlayer->SetX(pX);
					mPlayer->SetY(pY);
				}
			}
		}
	}
}

void CollisionManager::PlayerPhysics()
{
	RECT temp;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	if (mPlayer != nullptr)
	{
		float invincibleCount = mPlayer->GetInvincibleCount();
		RECT playerRC = mPlayer->GetCollisionBox();
		RECT enemyRC;
		vector<GameObject*> zombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
		if (zombie.size() != NULL)
		{
			for (int i = 0; i < zombie.size(); ++i)
			{
				enemyRC = ((Enemy*)zombie[i])->GetCollisionBox();
				if (IntersectRect(&temp, &playerRC, &enemyRC))	//플레이어 좀비 충돌 처리
				{
					float pX = mPlayer->GetX();
					float pY = mPlayer->GetY();
					float pSizeX = playerRC.bottom - playerRC.top;
					float pSizeY = playerRC.right - playerRC.left;

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
					if (tempW > tempH && tempY > enemyY && playerRC.top <= enemyRC.bottom)
					{
						pY = enemyRC.bottom + pSizeY / 2;
					}
					if (tempW > tempH && tempY < enemyY && playerRC.bottom >= enemyRC.top)
					{
						pY = enemyRC.top - pSizeY / 2;
					}

					mPlayer->SetX(pX);
					mPlayer->SetY(pY);

				}
			}
		}


		if (mPlayer->GetIsInvincible() == false) //플레이어 HP 변동
		{
			mPlayer->SetNoDamage(true);
			mPlayer->SetHP(mPlayer->GetHP() - 1);
		}
		if (mPlayer->GetInvincibleCount() == false)
		{
			invincibleCount += Time::GetInstance()->DeltaTime();
		}
		if (invincibleCount <= 0.3f && mPlayer->GetIsInvincible() == true)
		{
			//knockback(temp, 10.f);
		}
		if (invincibleCount > 1.5)
		{
			invincibleCount = 0;
			mPlayer->SetNoDamage(true);
		}
	}
}

void CollisionManager::PlayerTakenDamaged()
{
	RECT temp;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	if (mPlayer != nullptr)
	{
		float invincibleCount = mPlayer->GetInvincibleCount();
		RECT playerRC = mPlayer->GetRect();
		RECT enemyRC;
		vector<GameObject*> zombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
		if (zombie.size() != NULL)
		{
			for (int i = 0; i < zombie.size(); ++i)
			{
				enemyRC = ((Enemy*)zombie[i])->GetCollisionBox();
				if (IntersectRect(&temp, &playerRC, &enemyRC))	//플레이어 좀비 충돌 처리
				{
					float mAnlge = Math::GetAngle(zombie[i]->GetX(), zombie[i]->GetY()
						, mPlayer->GetX(), mPlayer->GetY());
					mPlayer->ExecuteKnockback(mAnlge, 500.f);

					//float pX = mPlayer->GetX();
					//float pY = mPlayer->GetY();
					//float pSizeX = mPlayer->GetSizeX();
					//float pSizeY = mPlayer->GetSizeY();

					//float tempW = temp.right - temp.left;
					//float tempH = temp.bottom - temp.top;
					//float tempX = temp.left + tempW / 2;
					//float tempY = temp.top + tempW / 2;
					//float enemyX = enemyRC.left + (enemyRC.right - enemyRC.left) / 2;
					//float enemyY = enemyRC.top + (enemyRC.bottom - enemyRC.top) / 2;

					//if (tempW < tempH && tempX > enemyX && playerRC.left < enemyRC.right)
					//{
					//	pX = enemyRC.right + pSizeX / 2;
					//					}
					//if (tempW < tempH && tempX < enemyX && playerRC.right > enemyRC.left)
					//{
					//	pX = enemyRC.left - pSizeX / 2;
					//}
					//if (tempW > tempH && tempY > enemyY && playerRC.top < enemyRC.bottom)
					//{
					//	pY = enemyRC.bottom + pSizeY / 2;
					//}
					//if (tempW > tempH && tempY < enemyY && playerRC.bottom > enemyRC.top)
					//{
					//	pY = enemyRC.top - pSizeY / 2;
					//}

					//mPlayer->SetX(pX);
					//mPlayer->SetY(pY);

				}
			}
		}


		if (mPlayer->GetIsInvincible() == false) //플레이어 HP 변동
		{
			mPlayer->SetNoDamage(true);
			mPlayer->SetHP(mPlayer->GetHP() - 1);
		}
		if (mPlayer->GetInvincibleCount() == false)
		{
			invincibleCount += Time::GetInstance()->DeltaTime();
		}
		if (invincibleCount <= 0.3f && mPlayer->GetIsInvincible() == true)
		{
			//knockback(temp, 10.f);
		}
		if (invincibleCount > 1.5)
		{
			invincibleCount = 0;
			mPlayer->SetNoDamage(true);
		}
	}


}

void CollisionManager::knockback(RECT temp, float Distance) 
{
	//float tempW = temp.right - temp.left;
	//float tempH = temp.bottom - temp.top;
	//float tempX = temp.right - tempW / 2;
	//float tempY = temp.bottom - tempH / 2;

	//// 좌상단 충돌
	//if(mPlayer->GetX() - tempX > 0 && mPlayer->GetY() - tempY > 0 && mPlayer->GetRect().top > temp.top) 
	//{
	//	mPlayer->SetAttacked(Attacked::lefttop);
	//}
	//// 좌하단 충돌
	//if (mPlayer->GetX() - tempX > 0 && mPlayer->GetY() - tempY < 0 && mPlayer->GetRect().bottom < temp.bottom) 
	//{
	//	mPlayer->SetAttacked(Attacked::leftdown);
	//}
	//// 우상단 충돌
	//if (mPlayer->GetX() - tempX < 0 && mPlayer->GetY() - tempY > 0 && mPlayer->GetRect().top > temp.top)
	//{
	//	mPlayer->SetAttacked(Attacked::righttop);
	//}
	//// 우하단 충돌
	//if (mPlayer->GetX() - tempX < 0 && mPlayer->GetY() - tempY < 0 && mPlayer->GetRect().bottom < temp.bottom)
	//{
	//	mPlayer->SetAttacked(Attacked::rightdown);
	//}
	//// 상단 충돌
	//if (mPlayer->GetRect().left <= temp.left && mPlayer->GetRect().right >= temp.right && mPlayer->GetY() > tempY)
	//{
	//	mPlayer->SetAttacked(Attacked::top);
	//}
	//// 하단 충돌
	//if (mPlayer->GetRect().left <= temp.left && mPlayer->GetRect().right >= temp.right && mPlayer->GetY() < tempY)
	//{
	//	mPlayer->SetAttacked(Attacked::down);
	//}
	//// 우측 충돌
	//if (mPlayer->GetRect().top <= temp.top && mPlayer->GetRect().bottom >= temp.bottom && mPlayer->GetX() > tempX)
	//{
	//	mPlayer->SetAttacked(Attacked::right);
	//}
	//// 좌측 충돌
	//if (mPlayer->GetRect().top <= temp.top && mPlayer->GetRect().bottom >= temp.bottom && mPlayer->GetX() < tempX)
	//{
	//	mPlayer->SetAttacked(Attacked::left);
	//}
}
