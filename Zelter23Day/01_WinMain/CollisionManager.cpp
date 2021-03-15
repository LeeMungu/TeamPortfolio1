#include "pch.h"
#include "CollisionManager.h"
#include "Player.h"
#include "ObjectManager.h"
#include "GameObject.h"


void CollisionManager::Update()
{
	PlayerCollion();
	PlayerTaken();
}

void CollisionManager::PlayerCollion()
{
	float damageCount = mPlayer->GetNoDamageCount();
	RECT temp;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	RECT playerRC = mPlayer->GetRect();
	vector<RECT> enemyRC;
	vector<GameObject*> zombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	for (int i = 0; i < zombie.size(); ++i)
	{	
		enemyRC.push_back( zombie[i]->GetRect());

		if (IntersectRect(&temp, &playerRC, &enemyRC[i]) && mPlayer->GetNoDamage() == true)
		{
			mPlayer->SetNoDamage(false);
			mPlayer->SetHP(mPlayer->GetHP() - 1);
			damageCount += Time::GetInstance()->DeltaTime();
		}
	}
	if (damageCount > 1.5)
	{
		damageCount = 0;
		mPlayer->SetNoDamage(true);
	}
}

void CollisionManager::PlayerTaken()
{
}
