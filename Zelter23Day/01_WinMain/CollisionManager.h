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


	void ObjectCollision(); //�÷��̾�� ������Ʈ �浹
	void ZombieCollision(); //�÷��̾�� ���� �浹
	void ZombieAttack(); //������ ���� (�÷��̾�, ������Ʈ ����)



};

