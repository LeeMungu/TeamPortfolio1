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
	PlayerCollision();
	ZombieAttack();
	PlayerAttack();
}



void CollisionManager::PlayerCollision()
{
	//�÷��̾�� ������Ʈ�� ������� ���մϴ�.
	RECT temp;
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

		//�÷��̾�� ���� ������� ���մϴ�.
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


void CollisionManager::ZombieAttack()
{
	RECT temp;
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

				if (IntersectRect(&temp, &playerRC, &enemyRC) && mPlayer->GetIsInvincible() == false)	//���� �÷��̾ �����Ͽ���!
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
						if (IntersectRect(&temp, &objectRC, &enemyRC) && tempInteractObject->GetIsInvincible() == false)	//���� ������Ʈ�� �����Ͽ���!
						{
							tempInteractObject->SetHp(tempInteractObject->GetHp() - 1);
							tempInteractObject->SetIsInvincible(true);
						}
					}
				}
			}
		}
	}
}


void CollisionManager::PlayerAttack()
{
	RECT temp;
	if (mPlayer != nullptr)
	{
		RECT playerAttackRC = mPlayer->GetAttackBox();
		RECT enemyRC;
		vector<GameObject*> zombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);

		if (zombie.size() != NULL)
		{
			for (int i = 0; i < zombie.size(); ++i)
			{
				Enemy* enemy = (Enemy*)zombie[i];
				enemyRC = enemy->GetRect();
				if (IntersectRect(&temp, &playerAttackRC, &enemyRC) && enemy->GetIsInvincible() == false)
				{
					float mAngle = Math::GetAngle(mPlayer->GetX(), mPlayer->GetY(), enemy->GetX(), enemy->GetY());
					enemy->SetHp(enemy->GetHP() - 1);
					enemy->ExecuteKnockback(mAngle, 200.f);
					enemy->SetIsInvincible(true);
				}
			}
		}

		RECT objectRC;
		vector<GameObject*> interactobject = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);
		if (interactobject.size() != NULL)
		{
			for (int i = 0; i < interactobject.size(); ++i)
			{
				InteractObject* tempinteractobject = (InteractObject*)interactobject[i];
				objectRC = tempinteractobject->GetInteractRect();
				if (IntersectRect(&temp, &playerAttackRC, &objectRC) && tempinteractobject->GetIsInvincible() == false)
				{
					tempinteractobject->SetHp(tempinteractobject->GetHp() - 1);
					tempinteractobject->SetIsInvincible(true);
				}
			}
		}
	}
}
