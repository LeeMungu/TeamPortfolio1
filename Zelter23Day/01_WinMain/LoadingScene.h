#pragma once
#include "Scene.h"
#include <functional>

class Animation;
class Image;
class LoadingScene : public Scene
{
	Image* mLoadingImage;
	Image* mLoadingImage2;
	Animation* mLoadingAnimation;

	vector<function<void(void)>> mLoadList;
	int mLoadIndex;
	bool mIsEndLoading;
	float mTime;
public:
	void AddLoadFunc(const function<void(void)>& func);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	bool GetIsEndLoading()const { return mIsEndLoading; }
};

