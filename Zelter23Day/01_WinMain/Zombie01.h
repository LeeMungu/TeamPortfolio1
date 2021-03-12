#pragma once
#include "Enemy.h"
class Image;
class Zombie01 : public Enemy
{
	
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Patrol();
	void SearchPlayer();
	void Attack()override;
};

