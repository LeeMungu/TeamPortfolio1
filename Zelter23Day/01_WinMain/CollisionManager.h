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


	void PlayerCollion();
	void PlayerTakenZombie(); //�÷��̾�� ���� �浹
	void knockback(RECT temp, float Distance); //�÷��̾� �˹� (���ͼ�Ʈ��Ʈ temp�� ����)


};

