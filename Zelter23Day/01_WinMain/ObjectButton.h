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
	function<void(void)> mFunc;	//��ư�������� ����� �Լ�
	int mIndexX;
	int mIndexY;
	State mState;
public:
	ObjectButton(wstring imageKey, float x, float y, function<void(void)> func);
	
	void Init()override {}
	void Release()override {}
	void Update()override;
	void Render(HDC hdc)override;

	void Move(float x, float y);
};

