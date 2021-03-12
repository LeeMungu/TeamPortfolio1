#pragma once
#include "Scene.h"
#include <functional>

class Animation;

class LoadingScene : public Scene
{
	Image* mLoadingImage;
	Animation* mLoadingAnimation;


	vector<function<void(void)>> mLoadList;
	int mLoadIndex;
	bool mIsEndLoading;
public:
	void AddLoadFunc(const function<void(void)>& func);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	bool GetIsEndLoading()const { return mIsEndLoading; }
};

