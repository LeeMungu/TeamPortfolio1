#pragma once
#include "GameObject.h"

class ObjectButton : public GameObject
{
	enum class State : int
	{
		Normal = 0,
		Push = 1,
		Select = 2,
		End
	};
	class Image* mImage;
	function<void(void)> mFunc;	//버튼눌렸을때 실행될 함수
	int mIndexX;
	int mIndexY;
	State mState;
public:
	ObjectButton(wstring imageKey, float x, float y, function<void(void)> func);
	
	void Init() {}
	void Release() {}
	void Update();
	void Render(HDC hdc);

	void Move(float x, float y);
};

