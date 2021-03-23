#pragma once
#include "GameObject.h"


class EffectImpact;
class EffectImpactManager :public GameObject
{
public:
	EffectImpact* mEffectImpact;
public:
	void Init(wstring imagekey, int x, int y, int indexX, int indexY);
	void Release();
	void Update();
	void Render(HDC hdc);

};

