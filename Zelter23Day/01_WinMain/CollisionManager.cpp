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
	RECT temp;
	mPlayer = (Player*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Player, "Player");
	RECT playerRC = mPlayer->GetRect();
	RECT enemyRC;
	vector<GameObject*> Zombie = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Enemy);
	for (int i = 0; i < Zombie.size(); ++i)
	{		
		if (IntersectRect(&temp, &playerRC, &enemyRC))
		{
			
		}
	}
}

void CollisionManager::PlayerTaken()
{
}
