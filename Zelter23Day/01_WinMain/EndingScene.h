#pragma once
#include "scene1.h"

class Image;
class EndingText;

class EndingScene : public scene1
{
	EndingText* mEndText;

	int mIndexY;
	bool mStop;
	Image* mImage;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


};

