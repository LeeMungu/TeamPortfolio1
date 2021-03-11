#pragma once
#include "UI.h"
class Image;
class SmartWatch : public UI
{
	Image* mBaseImage;
	Image* mGlassDark;
	Image* mGlass;
	Image* mTimeBG;
public:
	SmartWatch(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

