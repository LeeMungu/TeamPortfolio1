#pragma once
#include "Scene.h"

class MainScene : public Scene
{
	class Image* mImage;
	class Button* mStartButton;
	class Button* mToolSceneButton;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

