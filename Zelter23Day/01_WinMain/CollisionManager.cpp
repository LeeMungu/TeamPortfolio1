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
	ZombieCollision();
	ZombieAttack();
	PlayerCollision();
}


void CollisionManager::ObjectCollision()	
{

}

void CollisionManager::ZombieCollision()
{

}

void CollisionManager::PlayerCollision()
{
	//플레이어는 오브젝트를 통과하지 못합니다.
	RECT temp;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	if (mPlayer != nullptr)
	{
		RECT playerRC = mPlayer->GetCollisionBox();
		RECT objectRC;
		vector<GameObject*> object = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);
		if (object.size() != NULL)
		{
			for (int i = 0; i < object.size(); ++i)
			{
				objectRC = ((InteractObject*)object[i])->GetInteractRect();
				if (IntersectRect(&temp, &playerRC, &objectRC))
				{
					float pX = mPlayer->GetX();
					float pY = mPlayer->GetY();
					float pSizeX = playerRC.bottom - playerRC.top;
					float pSizeY = playerRC.right - playerRC.left;

					float tempW = temp.right - temp.left;
					float tempH = temp.bottom - temp.top;
					float tempX = temp.left + tempW / 2;
					float tempY = temp.top + tempH / 2;
					float ObjectX = objectRC.left + (objectRC.right - objectRC.left) / 2;
					float ObjectY = objectRC.top + (objectRC.bottom - objectRC.top) / 2;

					if (tempW < tempH && tempX > ObjectX && playerRC.left <= objectRC.right)
					{
						pX = objectRC.right + pSizeX / 2;
					}
					if (tempW < tempH && tempX < ObjectX && playerRC.right >= objectRC.left)
					{
						pX = objectRC.left - pSizeX / 2;
					}
					if (tempW > tempH && tempY > ObjectY && playerRC.top <= objectRC.bottom)
					{
						pY = objectRC.bottom + pSizeY / 2;
					}
					if (tempW > tempH && tempY < ObjectY && playerRC.bottom >= objectRC.top)
					{
						pY = objectRC.top - pSizeY / 2;
					}

					mPlayer->SetX(pX);
					mPlayer->SetY(pY);
				}
			}
		}

		//플레이어는 좀비를 통과하지 못합니다.
		RECT enemyRC;
		vector<GameObject*> zombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
		if (zombie.size() != NULL)
		{
			for (int i = 0; i < zombie.size(); ++i)
			{
				enemyRC = ((Enemy*)zombie[i])->GetCollisionBox();
				if (IntersectRect(&temp, &playerRC, &enemyRC))	
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
	}
}

void CollisionManager::PlayerAttack()
{
}

void CollisionManager::ZombieAttack()
{
	RECT temp;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	if (mPlayer != nullptr)
	{
		RECT playerRC = mPlayer->GetRect();
		RECT enemyRC;
		vector<GameObject*> zombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
		RECT objectRC;
		vector<GameObject*> interactobject = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);


		if (zombie.size() != NULL)
		{
			for (int i = 0; i < zombie.size(); ++i)
			{
				enemyRC = ((Enemy*)zombie[i])->GetAttackBox();

				if (IntersectRect(&temp, &playerRC, &enemyRC) && mPlayer->GetIsInvincible() == false)	//좀비가 플레이어를 공격하였다!
				{
					float mAnlge = Math::GetAngle(zombie[i]->GetX(), zombie[i]->GetY() , mPlayer->GetX(), mPlayer->GetY());
					mPlayer->ExecuteKnockback(mAnlge, 500.f);
					mPlayer->SetHP(mPlayer->GetHP() - 1);
					mPlayer->SetIsInvincible(true);
				}
				if (interactobject.size() != NULL)
				{
					for (int j = 0; j < interactobject.size(); ++j)
					{
						InteractObject* tempInteractObject =(InteractObject*)interactobject[j];
						objectRC = tempInteractObject->GetInteractRect();
						if (IntersectRect(&temp, &objectRC, &enemyRC) && tempInteractObject->GetIsInterRactive() == true)	//좀비가 오브젝트를 공격하였다!
						{
							tempInteractObject->SetHp(tempInteractObject->GetHp() - 1);
						}
					}
				}
			}
		}
	}
}
