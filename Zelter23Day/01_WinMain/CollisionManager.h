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

	//�÷��̾��� �̵��浹 (����, ������Ʈ)
	void PlayerCollision(); 
	//�÷��̾��� ���� (����, ������Ʈ)
	void PlayerAttack(); 
	//�÷��̾��� �߻� (����, ������Ʈ)
	void PlayerShoot();
	//������ ���� (�÷��̾�, ������Ʈ)
	void ZombieAttack();
	//������ �����̴�.
	void Boom();

};

