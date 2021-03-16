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


	void PlayerCollision();
	void PlayerPhysics(); //플레이어와 좀비 충돌
	void PlayerTakenDamaged(); //플레이어 피격
	void knockback(RECT temp, float Distance); //플레이어 넉백 (인터섹트렉트 temp값 기준)


};

