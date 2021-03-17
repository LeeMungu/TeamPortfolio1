#pragma once
#include "UI.h"
class Image;
class KeyIcon : public UI
{
	Image* mUIBaseImage;

public:
	KeyIcon(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

