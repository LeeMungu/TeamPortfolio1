#include "pch.h"
#include "CollisionManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "GameObject.h"
#include "InteractObject.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EffectManager.h"
#include "EffectImpact.h"


void CollisionManager::Init()
{
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
}

void CollisionManager::Update()
{
	PlayerCollision();
	ZombieAttack();
	PlayerAttack();
	PlayerShoot();
}



void CollisionManager::PlayerCollision()
{
	//플레이어는 오브젝트를 통과하지 못합니다.
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
					float pSizeX = playerRC.right - playerRC.left;
					float pSizeY = playerRC.bottom - playerRC.top;

					float tempW = temp.right - temp.left;
					float tempH = temp.bottom - temp.top;
					float tempX = temp.left + tempW / 2;
					float tempY = temp.top + tempH / 2;
					float ObjectX = objectRC.left + (objectRC.right - objectRC.left) / 2;
					float ObjectY = objectRC.top + (objectRC.bottom - objectRC.top) / 2;

					if (tempW < tempH && tempX > ObjectX && playerRC.left < objectRC.right)
					{
						pX = objectRC.right + pSizeX / 2;
					}
					if (tempW < tempH && tempX < ObjectX && playerRC.right > objectRC.left)
					{
						pX = objectRC.left - pSizeX / 2;
					}
					if (tempW > tempH && tempY > ObjectY && playerRC.top < objectRC.bottom)
					{
						pY = objectRC.bottom + pSizeY / 2;
					}
					if (tempW > tempH && tempY < ObjectY && playerRC.bottom > objectRC.top)
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
					float pSizeX = playerRC.right - playerRC.left;
					float pSizeY = playerRC.bottom - playerRC.top;

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
				Enemy* enemy = (Enemy*)zombie[i];
				enemyRC = enemy->GetAttackBox();
				//좀비가 플레이어를 공격하였다!
				if (IntersectRect(&temp, &playerRC, &enemyRC) && mPlayer->GetIsInvincible() == false)	
				{
					float mAnlge = Math::GetAngle(zombie[i]->GetX(), zombie[i]->GetY() , mPlayer->GetX(), mPlayer->GetY());
					mPlayer->ExecuteKnockback(mAnlge, 500.f);
					mPlayer->SetHP(mPlayer->GetHP() - 1);
					mPlayer->SetIsInvincible(true);
					enemy->SetIsAttackCheck(true);
					
				}
				else if (interactobject.size() != NULL)
				{
					for (int j = 0; j < interactobject.size(); ++j)
					{
						InteractObject* object =(InteractObject*)interactobject[j];
						objectRC = object->GetInteractRect();
						//좀비가 오브젝트를 공격하였다!
						if (IntersectRect(&temp, &objectRC, &enemyRC) && object->GetIsInvincible() == false)	
						{
							object->SetHp(object->GetHp() - 1);
							object->SetIsInvincible(true);
							enemy->SetIsAttackCheck(true);
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
				//플레이어가 좀비를 공격하였다!
				if (IntersectRect(&temp, &playerAttackRC, &enemyRC) && enemy->GetIsInvincible() == false)
				{
					float mAngle = Math::GetAngle(mPlayer->GetX(), mPlayer->GetY(), enemy->GetX(), enemy->GetY());
					enemy->SetHp(enemy->GetHP() - 1);
					enemy->ExecuteKnockback(mAngle, 200.f);
					enemy->SetIsInvincible(true);
					EffectManager* effect = new EffectManager(L"melee_attack", temp, 0, 5, 0.1f);

					EffectImpact* impact = new EffectImpact(enemy->GetX(), enemy->GetY(), 0, 0);

				}
			}
		}

		RECT objectRC;
		vector<GameObject*> interactobject = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);
		if (interactobject.size() != NULL)
		{
			for (int i = 0; i < interactobject.size(); ++i)
			{
				InteractObject* object = (InteractObject*)interactobject[i];
				objectRC = object->GetInteractRect();
				//플레이어가 오브젝트를 공격하였다!
				if (IntersectRect(&temp, &playerAttackRC, &objectRC) && object->GetIsInvincible() == false)
				{
					object->SetHp(object->GetHp() - 1);
					object->SetIsInvincible(true);
					EffectManager* effect = new EffectManager(L"melee_attack",temp,0,5,0.1f);
					EffectImpact* impact = new EffectImpact(object->GetX(), object->GetY(), 0, 0);
				}
			}
		}
	}
}

void CollisionManager::PlayerShoot()
{
	RECT temp;
	RECT bulletRC;
	vector<GameObject*> bulletList = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Bullet);
	RECT enemyRC;
	vector<GameObject*> zombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	RECT objectRC;
	vector<GameObject*> interactobject = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::InteractObject);

	if (bulletList.size() != NULL)
	{
		for (int i = 0; i < bulletList.size(); ++i)
		{
			Bullet* bullet  = (Bullet*) bulletList[i];
			bulletRC = bullet->GetRect();
			for (int j = 0; j < zombie.size(); j++)
			{
				Enemy* enemy = (Enemy*) zombie[j];
				enemyRC = enemy->GetRect();
				if (IntersectRect(&temp, &bulletRC, &enemyRC) &&  bullet->GetIsShot() == false)
				{
					if (enemy->GetIsInvincible() == false )
					{
						enemy->SetHp(enemy->GetHP() - 1);
						enemy->SetIsInvincible(true);

					}
					EffectManager* effect = new EffectManager(L"pistol_shoot", temp, 0, 6, 0.1f);
					bullet->SetIsShot(true);
				}
			}
			for (int k = 0; k < interactobject.size(); ++k)
			{
				InteractObject* object = (InteractObject*)interactobject[k];
				objectRC = object->GetInteractRect();
				if (IntersectRect(&temp, &bulletRC, &objectRC) && bullet->GetIsShot() == false)
				{
					if (object->GetIsInvincible() == false)
					{
						object->SetHp(object->GetHp() - 1);
						object->SetIsInvincible(true);
					}
					EffectManager* effect = new EffectManager(L"pistol_shoot", temp, 0, 6, 0.1f);
					bullet->SetIsShot(true);
				}
			}
		}
	}
}
