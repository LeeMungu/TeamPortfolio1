#pragma once
#include "UI.h"

class TextBox : public UI
{
	wstring mTextContext;
	class Image* mImage;
public:
	TextBox(wstring textContext);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

