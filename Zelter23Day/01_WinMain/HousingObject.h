#pragma once
#include "GameObject.h"
class HousingObject : public GameObject
{
public:
	HousingObject(const string& name);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

