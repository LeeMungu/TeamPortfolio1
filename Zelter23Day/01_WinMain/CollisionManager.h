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


	void PlayerCollision(); //�÷��̾��� �̵��浹 (����, ������Ʈ)
	void PlayerAttack(); //�÷��̾��� ���� (����, ������Ʈ)
	void ZombieAttack(); //������ ���� (�÷��̾�, ������Ʈ)

};

