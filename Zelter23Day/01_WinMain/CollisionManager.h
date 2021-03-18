#pragma once

class Player;
class Zombie01;
class CollisionManager
{
	Singleton(CollisionManager)

public:
	Player* mPlayer;


public:
	void Init();
	void Update();


	void ObjectCollision(); //플레이어와 오브젝트 충돌
	void ZombieCollision(); //플레이어와 좀비 충돌

	void PlayerCollision(); //플레이어의 이동충돌 (좀비, 오브젝트)
	void PlayerAttack(); //플레이어의 공격 (좀비, 오브젝트)
	void ZombieAttack(); //좀비의 공격 (플레이어, 오브젝트)

};

