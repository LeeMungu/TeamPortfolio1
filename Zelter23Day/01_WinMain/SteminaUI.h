#pragma once
#include "UI.h"
class SteminaUI : public UI
{
	Image* mEmptyGaugeImage;
	Image* mFullGaugeImage;
	Image* mIconImage;

	int mStemina;

public:
	SteminaUI(const string& name, int x, int y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetStemina(int s) { mStemina = s; }
};

