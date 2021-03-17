#pragma once
#include "UI.h"
class Image;
class KeyIcon : public UI
{
	Image* mBaseImage;

	Image* mBagIconImage;
	Image* mCraftIconImage;
	Image* mTabletIconImage;
	
	Image* mIKeyImage;
	Image* mCKeyImage;
	Image* mTKeyImage;

public:
	KeyIcon(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

