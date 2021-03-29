#pragma once
#include "Scene.h"

class MainScene : public Scene
{
	class Image* mImage;
	class Button* mStartButton;
	class Button* mToolSceneButton;
	class Button* mExitButton;

	bool mIsSkip;

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

