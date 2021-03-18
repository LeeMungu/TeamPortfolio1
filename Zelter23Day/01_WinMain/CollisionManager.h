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


	void PlayerCollision(); //플레이어의 이동충돌 (좀비, 오브젝트)
	void PlayerAttack(); //플레이어의 공격 (좀비, 오브젝트)
	void ZombieAttack(); //좀비의 공격 (플레이어, 오브젝트)

};

