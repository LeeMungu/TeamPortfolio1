#pragma once
#include "UI.h"
class SteminaUI : public UI
{
	Image* mEmptyGageImage;
	Image* mFullGageImage;
	Image* mIconImage;

	int mStemina;

public:
	SteminaUI(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

