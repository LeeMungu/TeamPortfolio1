#pragma once
#include "UI.h"
class Image;

class SmartWatch : public UI
{
	Image* mBaseImage;
	Image* mGlassDark;
	Image* mGlass;
	Image* mTimeBG;
	Image* mUIBaseImage;

	DayTime mDayTime;
	class PlayerHPUI* mPlayerHPUI;
	class ThirstUI* mThirstUI;
	class HungerUI* mHungerUI;
	class SteminaUI* mSteminaUI;

	class Player* mPlayer;

	int mHP;
	int mThirst;
	int mHunger;
	int mStemina;

	float mSceneTime;
	int mHour;
	int mMin;

public:
	SmartWatch(const string& name, int x, int y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetPlayer(Player* p) { mPlayer = p; }
};

