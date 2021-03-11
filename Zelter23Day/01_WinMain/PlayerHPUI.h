#pragma once
#include "UI.h"
class Image;
class Animation;

class PlayerHPUI : public UI
{
	Image* mBaseImage;
	Image* mEmptyGageImage;
	Image* mFullGageImage;
	Image* mHeartImage;

	int mHP;

	Animation* mHeartAnimation;
public:
	PlayerHPUI(const string& name, int x, int y); 
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

