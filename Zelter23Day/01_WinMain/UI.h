#pragma once
#include "GameObject.h"
class UI : public GameObject
{
public:
	UI(const string& name);

	virtual void Init()override = 0;
	virtual void Release()override = 0;
	virtual void Update()override = 0;
	virtual void Render(HDC hdc)override = 0;
};

