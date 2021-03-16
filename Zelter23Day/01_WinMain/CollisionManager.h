#pragma once

class Player;
class Zombie01;
class CollisionManager
{
	Singleton(CollisionManager)

public:
	Player* mPlayer;

public:
	void Update();

	void PlayerCollion();
	void PlayerTakenZombie(); //플레이어와 좀비 충돌
	void knockback();


};

