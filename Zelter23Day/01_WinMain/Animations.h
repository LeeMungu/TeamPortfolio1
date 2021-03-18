#pragma once
#include "Animation.h"
template<typename T>
class Animations final
{
	map<T, Animation*> mAnimationList;
	Animation* mCurrentAnimation;
	typedef map<wstring, Animation*>::iterator Animationiter;
	//typedef map<ObjectLayer, vector<class GameObject*>>::iterator ObjectIter;
	
public:
	Animations() :mCurrentAnimation(nullptr) {}
	~Animations()
	{
		Animationiter iter = mAnimationList.begin();
		for (; iter != mAnimationList.end(); ++iter)
		{
			SafeDelete(iter->second);
		}
	}

	void Update()
	{
		if (mCurrentAnimation)
			mCurrentAnimation->Update();
	}

	void AddAnimation(T key, Animation* animation)
	{
		mAnimationList.insert(make_pair(key, animation));
	}

	Animation* GetCurrentAnimation()const { return mCurrentAnimation; }

	int CurrentIndexX()const { return mCurrentAnimation->GetNowFrameX(); }
	int CurrentIndexY()const { return mCurrentAnimation->GetNowFrameY(); }
};

