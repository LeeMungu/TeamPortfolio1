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
	void PlayerPhysics(); //�÷��̾�� ���� �浹
	void PlayerTakenDamaged(); //�÷��̾� �ǰ�
	void knockback(RECT temp, float Distance); //�÷��̾� �˹� (���ͼ�Ʈ��Ʈ temp�� ����)


};

