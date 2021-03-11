#pragma once
#include "UI.h"
class Image;
enum class DayTime {
	morning,
	night,
};
class SmartWatch : public UI
{
	Image* mBaseImage;
	Image* mGlassDark;
	Image* mGlass;
	Image* mTimeBG;

	DayTime mDayTime;
public:
	SmartWatch(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

