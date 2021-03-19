#pragma once
#include "UI.h"
class Image;
class Animation;

class PlayerHPUI : public UI
{
	Image* mBaseImage;
	Image* mEmptyGaugeImage;
	Image* mFullGaugeImage;
	Image* mHeartImage;

	float mHP;

	Animation* mHeartAnimation;
public:
	PlayerHPUI(const string& name, int x, int y); 
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetHP(int h) { mHP = h; }
};

